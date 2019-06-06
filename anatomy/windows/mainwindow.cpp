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

#include <QDialog>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Início");
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Selecione a Tarefa"), "JSON (*.json)");
    QJsonDocument assignmentDocument = LoadJson(fileName);
    SaveAssignmentFromJSON(assignmentDocument.object());
}

QJsonDocument MainWindow::LoadJson(QString &fileName)
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

bool MainWindow::SaveAssignmentFromJSON(QJsonObject jsonObject)
{
    DAOModality *daoModality = new DAOModalitySQLITE();
    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE();

    Modality modality = Modality(jsonObject["ModalityDescription"].toString());
    daoModality->addModality(&modality);

    AnatomicalRegion anatomicalRegion = AnatomicalRegion(jsonObject["AnatomicalRegionDescription"].toString());
    anatomicalRegion.setModalityId(daoModality->getModalityByDescription(modality.description()).id());
    daoAnatomicalRegion->addAnatomicalRegion(&anatomicalRegion);

//    Name = json["name"].toString();
//      mLevel = json["level"].toDouble();
//      mClassType = ClassType(qRound(json["classType"].toDouble()));
}

