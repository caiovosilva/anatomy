#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newquestionwindow.h"
#include "listquestionswindow.h"

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
    NewQuestionWindow *newWindow = new NewQuestionWindow;
    newWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    ListQuestionsWindow *newWindow = new ListQuestionsWindow;
    newWindow->show();
}
