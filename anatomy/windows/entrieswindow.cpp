#include "entrieswindow.h"
#include "ui_entrieswindow.h"

#include "newquestionwindow.h"
#include "newmodalitywindow.h"
#include "newanatomyimagewindow.h"
#include "newassignmentwindow.h"
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
    newWindow->setWindowTitle("Modalidades");
    newWindow->show();
}
void EntriesWindow::on_newAnatomicalRegionButton_clicked()
{
    AnatomicalRegionList *newWindow = new AnatomicalRegionList;
    newWindow->show();

}

void EntriesWindow::on_newAssignmentButton_clicked()
{
    NewAssignmentWindow *newWindow = new NewAssignmentWindow;
    newWindow->show();
}

void EntriesWindow::on_newQuestionButton_clicked()
{
    NewQuestionWindow *newWindow = new NewQuestionWindow;
    newWindow->setWindowTitle("Nova Questão");
    newWindow->show();
}
