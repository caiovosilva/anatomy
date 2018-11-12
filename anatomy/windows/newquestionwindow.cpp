#include "newquestionwindow.h"
#include "ui_newquestionwindow.h"

#include <QMessageBox>

#include "model/question.h"
#include "model/answer.h"
#include "model/assignment.h"
#include "model/modality.h"
#include "DAO/daoassignmentsqlite.h"
#include "DAO/daoquestionsqlite.h"
#include "DAO/daoanswersqlite.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoanatomicalregionsqlite.h"

NewQuestionWindow::NewQuestionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewQuestionWindow)
{
    ui->setupUi(this);


    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        ui->modalitiesComboBox->addItem(item.description(), item.id());
    }
}

NewQuestionWindow::~NewQuestionWindow()
{
    delete ui;
}

bool NewQuestionWindow::oneCorrectAnswerSelected()
{
    if(ui->correctAnswer1->isChecked()|| ui->correctAnswer2->isChecked() || ui->correctAnswer3->isChecked() || ui->correctAnswer4->isChecked())
        return true;
    return false;
}

bool NewQuestionWindow::allAnswersAndQuestionFilled()
{
    if(ui->question->toPlainText().isEmpty() || ui->answer1->toPlainText().isEmpty() || ui->answer2->toPlainText().isEmpty() ||
            ui->answer3->toPlainText().isEmpty() || ui->answer4->toPlainText().isEmpty())
        return false;
    return true;
}

void NewQuestionWindow::on_cancelButton_clicked()
{
    this->close();

}

void NewQuestionWindow::on_saveButton_clicked()
{
    if(saveQuestion())
        on_cancelButton_clicked();
}

bool NewQuestionWindow::saveQuestion()
{

    if(!oneCorrectAnswerSelected())
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Selecione uma resposta correta.");
        msg.exec();
        return false;
    }
    if(!allAnswersAndQuestionFilled())
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Preencha a pergunta e todos os campos de respostas.");
        msg.exec();
        return false;
    }

    int assignmentId = ui->assignmentComboBox->currentData().toInt();
    Question question = Question(ui->question->toPlainText(), assignmentId);

    DAOQuestion *daoQuestion = new DAOQuestionSQLITE;
    if(daoQuestion->addQuestion(&question))
    {
            DAOAnswer *daoAnswer = new DAOAnswerSQLITE;
            Answer answer;
            answer = Answer(ui->answer1->toPlainText(), ui->correctAnswer1->isChecked(), question.id());
            daoAnswer->addAnswer(&answer);
            if(answer.isCorrectAnswer())
                question.setCorrectAnswerId(answer.id());
            answer = Answer(ui->answer2->toPlainText(), ui->correctAnswer2->isChecked(), question.id());
            daoAnswer->addAnswer(&answer);
            if(answer.isCorrectAnswer())
                question.setCorrectAnswerId(answer.id());
            answer = Answer(ui->answer3->toPlainText(), ui->correctAnswer3->isChecked(), question.id());
            daoAnswer->addAnswer(&answer);
            if(answer.isCorrectAnswer())
                question.setCorrectAnswerId(answer.id());
            answer = Answer(ui->answer4->toPlainText(), ui->correctAnswer4->isChecked(), question.id());
            daoAnswer->addAnswer(&answer);
            if(answer.isCorrectAnswer())
                question.setCorrectAnswerId(answer.id());

            daoQuestion->updateQuestion(&question);
    }
    return true;
}

void NewQuestionWindow::on_saveAndContinueButton_clicked()
{
    if(saveQuestion())
        ui->answer1->clear();
        ui->answer2->clear();
        ui->answer3->clear();
        ui->answer4->clear();
        ui->question->clear();

}

void NewQuestionWindow::on_modalitiesComboBox_currentIndexChanged(int index)
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

void NewQuestionWindow::on_anatomicalRegionComboBox_currentIndexChanged(int index)
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
