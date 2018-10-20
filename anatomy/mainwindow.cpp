#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newquestionwindow.h"

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
    NewQuestionWindow *newQuestion = new NewQuestionWindow;
    //this->close();
    newQuestion->show();
}
