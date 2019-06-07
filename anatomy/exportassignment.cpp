#include "exportassignment.h"
#include "ui_exportassignment.h"

#include <QFileDialog>

#include "model/question.h"
#include "model/answer.h"
#include "model/assignment.h"
#include "model/modality.h"
#include "DAO/daoassignmentsqlite.h"
#include "DAO/daoquestionsqlite.h"
#include "DAO/daoanswersqlite.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoanatomicalregionsqlite.h"

ExportAssignment::ExportAssignment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportAssignment)
{
    ui->setupUi(this);

    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        ui->modalityComboBox->addItem(item.description(), item.id());
    }

    delete daoModality;
}

ExportAssignment::~ExportAssignment()
{
    delete ui;
}

void ExportAssignment::on_buttonBox_accepted()
{
    int assignmentId = ui->assignmentComboBox->currentData().toInt();
    DAOAssignment *daoAssignmet = new DAOAssignmentSQLITE;
    Assignment  assignment = daoAssignmet->getAssignmentById(assignmentId);

    QJsonObject jsonObject = ConvertAssignmentToJson(assignment);
    DownloadAssignment(jsonObject, assignment.description());
//    PlayWindow *newWindow = new PlayWindow(assignmentId, ui->studentName->toPlainText());
//    newWindow->setWindowTitle("Tarefa");
//    newWindow->show();
}

void ExportAssignment::on_modalityComboBox_currentIndexChanged(int index)
{
    int modalityId = ui->modalityComboBox->currentData().toInt();

    QList<AnatomicalRegion> anatomicalRegionList;
    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE;
    anatomicalRegionList = daoAnatomicalRegion->getAnatomicalRegionByModalityId(modalityId);

    ui->anatomicalRegionComboBox->clear();
    foreach (AnatomicalRegion item, anatomicalRegionList) {
        ui->anatomicalRegionComboBox->addItem(item.description(), item.id());
    }

    delete daoAnatomicalRegion;
}

QJsonObject ExportAssignment::ConvertAssignmentToJson(Assignment &assignment)
{
    QJsonObject recordObject;
    recordObject.insert("Description", QJsonValue::fromVariant(assignment.description()));

    QJsonArray imagesArray;
    QString s_data;
    foreach (AnatomyImage anatomyImage, assignment.anatomyImageList()) {
        s_data = QString::fromLatin1(anatomyImage.image());
        imagesArray.push_back(QString::fromLatin1(anatomyImage.image()));
    }
    recordObject.insert("Images", imagesArray);

    QJsonArray questionsArray;
    foreach (Question question, assignment.questionsList()) {
        QJsonObject questionObject;
        questionObject.insert("Description", QJsonValue::fromVariant(question.description()));

        QJsonArray answersArray;
        foreach (Answer answer, question.answers()) {
            QJsonObject asw;
            asw.insert("Description", QJsonValue::fromVariant(answer.description()));
            asw.insert("IsCorrectAnswer", QJsonValue::fromVariant(answer.isCorrectAnswer()));
            answersArray.push_back(asw);
        }

        questionObject.insert("Answers", answersArray);
        questionsArray.push_back(questionObject);
    }
    recordObject.insert("Questions", questionsArray);

    AnatomicalRegion anatomicalRegion;
    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE;
    anatomicalRegion = daoAnatomicalRegion->getAnatomicalRegionById(assignment.anatomicalRegionId());
    recordObject.insert("AnatomicalRegionDescription", anatomicalRegion.description());

    Modality modality;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modality = daoModality->getModalityById(anatomicalRegion.modalityId());
    recordObject.insert("ModalityDescription", modality.description());

    return recordObject;
}

void ExportAssignment::DownloadAssignment(QJsonObject &jsonObject, QString title)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salvar Arquivo"), title+".json");

    QFile saveFile(fileName);
    if (!saveFile.open(QIODevice::WriteOnly))
        qWarning("Couldn't open save file.");
    QJsonDocument saveDoc(jsonObject);
    saveFile.write(saveDoc.toJson());
}

void ExportAssignment::on_anatomicalRegionComboBox_currentIndexChanged(int index)
{
    int anatomicalRegionId = ui->anatomicalRegionComboBox->currentData().toInt();

    QList<Assignment> assignmentList;
    DAOAssignment *assignmentDAO = new DAOAssignmentSQLITE;
    DAOQuestion *questionsDAO = new DAOQuestionSQLITE;
    assignmentList = assignmentDAO->getAssignmentsByAnatomicalRegion(anatomicalRegionId);

    ui->assignmentComboBox->clear();
    foreach (Assignment item, assignmentList) {
        item.setQuestionsList(questionsDAO->getQuestionsByAssignmentId(item.id()));
        ui->assignmentComboBox->addItem(item.description(), item.id());
    }
}
