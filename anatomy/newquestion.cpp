#include "newquestion.h"
#include "ui_newquestion.h"

#include <QMessageBox>

#include "question.h"
#include "answer.h"

NewQuestion::NewQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewQuestion)
{
    ui->setupUi(this);
}

NewQuestion::~NewQuestion()
{
    delete ui;
}

void NewQuestion::on_buttonBox_accepted()
{
    if(!oneCorrectAnswerSelected())
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Selecione uma resposta correta.");
        msg.exec();
    }

    Question *question = new Question();
    question->description = ui->question->toPlainText();


}

bool NewQuestion::oneCorrectAnswerSelected()
{
//    foreach(QRadioButton answer, answerButtons)
//        if(answer.isChecked())
//            return true;
    return false;
}
