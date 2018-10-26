#include "newquestionwindow.h"
#include "ui_newquestionwindow.h"

#include <QMessageBox>

#include "question.h"
#include "answer.h"

NewQuestionWindow::NewQuestionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewQuestionWindow)
{
    ui->setupUi(this);
}

NewQuestionWindow::~NewQuestionWindow()
{
    delete ui;
}

void NewQuestionWindow::on_buttonBox_accepted()
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

//    Question question = Question(ui->question->toPlainText());

//    Answer answer = Answer(ui->answer1->toPlainText(), ui->correctAnswer1->isChecked());
//    question.addAnswer(&answer);
//    answer = Answer(ui->answer2->toPlainText(), ui->correctAnswer2->isChecked());
//    question.addAnswer(&answer);
//    answer = Answer(ui->answer3->toPlainText(), ui->correctAnswer3->isChecked());
//    question.addAnswer(&answer);
//    answer = Answer(ui->answer4->toPlainText(), ui->correctAnswer4->isChecked());
//    question.addAnswer(&answer);
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
