#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newquestionwindow.h"
#include "listquestionswindow.h"
#include "playwindow.h"
#include "entrieswindow.h"
#include "DAO/dbconnection.h"
#include "DAO/daoanatomyimagesqlite.h"
#include "assignmentchooser.h"

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
    ListQuestionsWindow *newWindow = new ListQuestionsWindow;
    newWindow->setWindowTitle("Questões");
    newWindow->show();
}

void MainWindow::on_init_clicked()
{
    AssignmentChooser *newWindow = new AssignmentChooser;
    newWindow->setWindowTitle("Escolha Uma Tarefa");
    newWindow->show();
}
