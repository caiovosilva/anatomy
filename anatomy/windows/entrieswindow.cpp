#include "entrieswindow.h"
#include "ui_entrieswindow.h"

#include "newquestionwindow.h"
#include "newmodalitywindow.h"

EntriesWindow::EntriesWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntriesWindow)
{
    ui->setupUi(this);
}

EntriesWindow::~EntriesWindow()
{
    delete ui;
}

void EntriesWindow::on_newModalityButton_clicked()
{
    NewModalityWindow *newWindow = new NewModalityWindow;
    newWindow->show();
}
