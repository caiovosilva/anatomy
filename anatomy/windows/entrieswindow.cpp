#include "entrieswindow.h"
#include "ui_entrieswindow.h"

#include "questionlist.h"
#include "newmodalitywindow.h"
#include "assignmentlist.h"
#include "modalitylist.h"
#include "anatomicalregionlist.h"

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

void EntriesWindow::on_modalityButton_clicked()
{
    ModalityList *newWindow = new ModalityList;
    newWindow->show();
}
void EntriesWindow::on_newAnatomicalRegionButton_clicked()
{
    AnatomicalRegionList *newWindow = new AnatomicalRegionList;
    newWindow->show();
}

void EntriesWindow::on_newAssignmentButton_clicked()
{
    AssignmentList *newWindow = new AssignmentList;
    newWindow->show();
}

void EntriesWindow::on_newQuestionButton_clicked()
{
    QuestionList *newWindow = new QuestionList;
    newWindow->show();
}
