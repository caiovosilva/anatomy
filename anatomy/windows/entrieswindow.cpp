#include "entrieswindow.h"
#include "ui_entrieswindow.h"

#include "newquestionwindow.h"
#include "newmodalitywindow.h"
#include "newanatomicalregionwindow.h"
#include "newanatomyimagewindow.h"
#include "newassignmentwindow.h"

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
    newWindow->setWindowTitle("Nova Modalidade");
    newWindow->show();
}
void EntriesWindow::on_newAnatomicalRegionButton_clicked()
{
    NewAnatomicalRegionWindow *newWindow = new NewAnatomicalRegionWindow;
    newWindow->setWindowTitle("Nova Região Anatômica");
    newWindow->show();
}

void EntriesWindow::on_newAssignmentButton_clicked()
{
    NewAssignmentWindow *newWindow = new NewAssignmentWindow;
    newWindow->setWindowTitle("Nova Tarefa");
    newWindow->show();
}

void EntriesWindow::on_newQuestionButton_clicked()
{
    NewQuestionWindow *newWindow = new NewQuestionWindow;
    newWindow->setWindowTitle("Nova Questão");
    newWindow->show();
}
