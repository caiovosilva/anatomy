#include "exportassignment.h"
#include "ui_exportassignment.h"

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
