#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newquestionwindow.h"
#include "listquestionswindow.h"
#include "playwindow.h"
#include "entrieswindow.h"
#include "DAO/dbconnection.h"
#include "DAO/daoanatomyimagesqlite.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    EntriesWindow *newWindow = new EntriesWindow;
    newWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    ListQuestionsWindow *newWindow = new ListQuestionsWindow;
    newWindow->show();
}

void MainWindow::on_init_clicked()
{
//    PlayWindow *newWindow = new PlayWindow;
//    newWindow->show();
}
