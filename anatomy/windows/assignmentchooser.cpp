#include "assignmentchooser.h"
#include "ui_assignmentchooser.h"

#include "model/question.h"
#include "model/answer.h"
#include "model/assignment.h"
#include "model/modality.h"
#include "DAO/daoassignmentsqlite.h"
#include "DAO/daoquestionsqlite.h"
#include "DAO/daoanswersqlite.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoanatomicalregionsqlite.h"
#include "playwindow.h"

AssignmentChooser::AssignmentChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssignmentChooser)
{
    ui->setupUi(this);

    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        ui->modalitiesComboBox->addItem(item.description(), item.id());
    }
}

AssignmentChooser::~AssignmentChooser()
{
    delete ui;
}

void AssignmentChooser::on_modalitiesComboBox_currentIndexChanged(int index)
{
    int modalityId = ui->modalitiesComboBox->currentData().toInt();

    QList<AnatomicalRegion> anatomicalRegionList;
    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE;
    anatomicalRegionList = daoAnatomicalRegion->getAnatomicalRegionByModalityId(modalityId);

    ui->anatomicalRegionComboBox->clear();
    foreach (AnatomicalRegion item, anatomicalRegionList) {
        ui->anatomicalRegionComboBox->addItem(item.description(), item.id());
    }
}

void AssignmentChooser::on_anatomicalRegionComboBox_currentIndexChanged(int index)
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

void AssignmentChooser::on_buttonBox_accepted()
{
    int assignmentId = ui->assignmentComboBox->currentData().toInt();
    PlayWindow *newWindow = new PlayWindow(assignmentId, ui->studentName->toPlainText());
    newWindow->setWindowTitle("Tarefa");
    newWindow->show();

}
