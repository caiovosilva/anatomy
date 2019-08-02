#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newquestionwindow.h"
#include "playwindow.h"
#include "entrieswindow.h"
#include "DAO/dbconnection.h"
#include "DAO/daoanatomyimagesqlite.h"
#include "assignmentchooser.h"
#include "exportassignment.h"
#include "DAO/daoanatomicalregionsqlite.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoassignmentsqlite.h"
#include "DAO/daoquestionsqlite.h"
#include "DAO/daoanswersqlite.h"
#include <QDesktopWidget>
#include <QDialog>
#include <QDialogButtonBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Início");

    QPixmap gteclogo(":/images/images/gtecradlogo.png");
    int w = ui->gtecradlogo->width();
    int h = ui->gtecradlogo->height();
    ui->gtecradlogo->setPixmap(gteclogo.scaled(w,h,Qt::KeepAspectRatio));
    QPixmap ifbalogo(":/images/images/ifbalogo.jpg");
    w = ui->ifbalogo->width();
    h = ui->ifbalogo->height();
    ui->ifbalogo->setPixmap(ifbalogo.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    EntriesWindow *newWindow = new EntriesWindow;
    newWindow->setWindowTitle("Cadastros");
    newWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    ExportAssignment *newWindow = new ExportAssignment;
    newWindow->setWindowTitle("Exportar Tarefa");
    newWindow->show();
}

void MainWindow::on_init_clicked()
{
    AssignmentChooser *newWindow = new AssignmentChooser;
    newWindow->setWindowTitle("Escolha Uma Tarefa");
    newWindow->show();
}

void MainWindow::on_importPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Selecione a Tarefa"),"/home", "DAT (*.dat)");
    if(fileName.isEmpty())
        return;
    QJsonDocument assignmentDocument = loadJson(fileName);
    bool result = saveAssignmentFromJSON(assignmentDocument.object());

    if(result){
        QMessageBox msg(QMessageBox::Information, "Sucesso", "Tarefa importada!");
        msg.exec();
    }
    else {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Ocorreu um erro ao importar tarefa.");
        msg.exec();
    }
}

QJsonDocument MainWindow::loadJson(QString &fileName)
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromBinaryData(jsonFile.readAll());
}

bool MainWindow::saveAssignmentFromJSON(QJsonObject jsonObject)
{
    DAOModality *daoModality = new DAOModalitySQLITE();
    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE();
    DAOAssignment *daoAssignment = new DAOAssignmentSQLITE();
    DAOAnatomyImage *daoAnatomyImage = new DAOAnatomyImageSQLITE();
    DAOQuestion *daoQuestion = new DAOQuestionSQLITE();
    DAOAnswer *daoAnswer = new DAOAnswerSQLITE();
    bool result = true;

    Modality modality = Modality(jsonObject["ModalityDescription"].toString());
    daoModality->addOrUpdateModality(&modality);

    AnatomicalRegion anatomicalRegion = AnatomicalRegion(jsonObject["AnatomicalRegionDescription"].toString());
    anatomicalRegion.setModalityId(daoModality->getModalityByDescription(modality.description()).id());
    daoAnatomicalRegion->addOrUpdateAnatomicalRegion(&anatomicalRegion);

    QString description = jsonObject["Description"].toString();
    Assignment assignment = Assignment(description,
            daoAnatomicalRegion->getAnatomicalRegionByDescription(anatomicalRegion.description()).id());
    if(daoAssignment->getAssignmentByDescription(description) != nullptr)
        for (int var = 2; var < 500; var++)
            if(daoAssignment->getAssignmentByDescription(description+" ("+QString::number(var)+")") == nullptr) {
                assignment.setDescription(description+" ("+QString::number(var)+")");
                break;
            }
    result = result && daoAssignment->addOrUpdateAssignment(&assignment);

    QJsonArray imagesArray = jsonObject["Images"].toArray();
    for (int imageIndex = 0; imageIndex < imagesArray.size(); ++imageIndex) {
        AnatomyImage image;
        QByteArray ba;
        ba.append(imagesArray[imageIndex].toString());
        ba = QByteArray::fromBase64(ba);
        image.setImage(ba);
        image.setAssignmentId(assignment.id());
        daoAnatomyImage->addAnatomyImage(&image);
    }

    QJsonArray questionsArray = jsonObject["Questions"].toArray();
    for(int i=0;i < questionsArray.size();i++) {
        QJsonObject questionObj = questionsArray.at(i).toObject();
        QString questionDescription = questionObj["Description"].toString();
        Question question = Question(questionDescription, assignment.id());
        result = result && daoQuestion->addOrUpdateQuestion(&question);

        QJsonArray answersArray = questionObj["Answers"].toArray();
        for(int i=0;i < answersArray.size();i++) {
            QJsonObject answerObj = answersArray.at(i).toObject();
            QString answerDescription = answerObj["Description"].toString();
            Answer answer = Answer(answerObj["Description"].toString(), answerObj["IsCorrectAnswer"].toBool(), question.id());
            result = result && daoAnswer->addOrUpdateAnswer(&answer);
        }
    }
    return result;
}

