#include "newquestionwindow.h"
#include "ui_newquestionwindow.h"

#include <QMessageBox>

#include "model/question.h"
#include "model/answer.h"
#include "DAO/daoanatomyimagesqlite.h"
#include "DAO/daoquestionsqlite.h"
#include "DAO/daoanswersqlite.h"

NewQuestionWindow::NewQuestionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewQuestionWindow)
{
    ui->setupUi(this);

    QList<AnatomyImage> anatomyList;
    DAOAnatomyImage *anatomyDAO = new DAOAnatomyImageSQLITE;
    DAOQuestion *questionsDAO = new DAOQuestionSQLITE;
    anatomyList = anatomyDAO->getAllAnatomyImages();

    foreach (AnatomyImage item, anatomyList) {
        item.setQuestionsList(questionsDAO->getQuestionsByAnatomyImageId(item.getId()));
        ui->anatomyComboBox->addItem(item.getDescription(), item.getId());
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
    saveQuestion();
    on_cancelButton_clicked();
}

void NewQuestionWindow::saveQuestion()
{
    if(!oneCorrectAnswerSelected())
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Selecione uma resposta correta.");
        msg.exec();
        return;
    }
    if(!allAnswersAndQuestionFilled())
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Preencha a pergunta e todos os campos de respostas.");
        msg.exec();
        return;
    }

    int id = ui->anatomyComboBox->currentData().toInt();
    Question question = Question(ui->question->toPlainText(), id);

    DAOQuestion *daoQuestion = new DAOQuestionSQLITE;
    if(daoQuestion->addQuestion(&question))
    {
            DAOAnswer *daoAnswer = new DAOAnswerSQLITE;
            Answer answer;
            answer = Answer(ui->answer1->toPlainText(), ui->correctAnswer1->isChecked(), question.id());
            daoAnswer->addAnswer(&answer);
            answer = Answer(ui->answer2->toPlainText(), ui->correctAnswer2->isChecked(), question.id());
            daoAnswer->addAnswer(&answer);
            answer = Answer(ui->answer3->toPlainText(), ui->correctAnswer3->isChecked(), question.id());
            daoAnswer->addAnswer(&answer);
            answer = Answer(ui->answer4->toPlainText(), ui->correctAnswer4->isChecked(), question.id());
            daoAnswer->addAnswer(&answer);
    }
}

void NewQuestionWindow::on_saveAndContinueButton_clicked()
{
    saveQuestion();

    ui->answer1->clear();
    ui->answer2->clear();
    ui->answer3->clear();
    ui->answer4->clear();
    ui->question->clear();

}
