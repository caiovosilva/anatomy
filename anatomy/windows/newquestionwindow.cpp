#include "newquestionwindow.h"
#include "ui_newquestionwindow.h"

#include <QMessageBox>

#include "model/answer.h"
#include "model/assignment.h"
#include "model/modality.h"
#include "DAO/daoassignmentsqlite.h"
#include "DAO/daoquestionsqlite.h"
#include "DAO/daoanswersqlite.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoanatomicalregionsqlite.h"

NewQuestionWindow::NewQuestionWindow(Question *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewQuestionWindow)
{
    ui->setupUi(this);
    setWindowTitle("Questão");

    if(model != nullptr) {
        _model.setDescription(model->description());
        _model.setId(model->id());
        _model.setAnswers(model->answers());
        _model.setAssignmentId(model->assignmentId());
        _answer1.setId(_model.answers().at(0).id());
        _answer1.setQuestionId(_model.id());
        _answer1.setDescription(_model.answers().at(0).description());
        _answer1.setIsCorrectAnswer(_model.answers().at(0).isCorrectAnswer());
        _answer2.setId(_model.answers().at(1).id());
        _answer2.setQuestionId(_model.id());
        _answer2.setDescription(_model.answers().at(1).description());
        _answer2.setIsCorrectAnswer(_model.answers().at(1).isCorrectAnswer());
        _answer3.setId(_model.answers().at(2).id());
        _answer3.setQuestionId(_model.id());
        _answer3.setDescription(_model.answers().at(2).description());
        _answer3.setIsCorrectAnswer(_model.answers().at(2).isCorrectAnswer());
        _answer4.setId(_model.answers().at(3).id());
        _answer4.setQuestionId(_model.id());
        _answer4.setDescription(_model.answers().at(3).description());
        _answer4.setIsCorrectAnswer(_model.answers().at(3).isCorrectAnswer());

        ui->question->setText(_model.description());
        ui->answer1->setText(_answer1.description());
        ui->correctAnswer1->setChecked(_answer1.isCorrectAnswer());
        ui->answer2->setText(_answer2.description());
        ui->correctAnswer2->setChecked(_answer2.isCorrectAnswer());
        ui->answer3->setText(_answer3.description());
        ui->correctAnswer3->setChecked(_answer3.isCorrectAnswer());
        ui->answer4->setText(_answer4.description());
        ui->correctAnswer4->setChecked(_answer4.isCorrectAnswer());
    }

    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        ui->modalitiesComboBox->addItem(item.description(), item.id());
    }

    delete daoModality;
}

NewQuestionWindow::NewQuestionWindow(Assignment model, QWidget *parent): NewQuestionWindow(){

    AnatomicalRegion anatomicalRegion = (new DAOAnatomicalRegionSQLITE)->getAnatomicalRegionById(model.anatomicalRegionId());
    int assignmentId = model.id();
    int anatomicalRegionId = anatomicalRegion.id();
    int modalityId = anatomicalRegion.modalityId();
    int index = ui->modalitiesComboBox->findData(modalityId);
    ui->modalitiesComboBox->setCurrentIndex(index);
    index = ui->anatomicalRegionComboBox->findData(anatomicalRegionId);
    ui->anatomicalRegionComboBox->setCurrentIndex(index);
    index = ui->assignmentComboBox->findData(assignmentId);
    ui->assignmentComboBox->setCurrentIndex(index);
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
        close();
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
    _model.setDescription(ui->question->toPlainText());
    _model.setAssignmentId(assignmentId);
    _answer1.setDescription(ui->answer1->toPlainText());
    _answer1.setIsCorrectAnswer(ui->correctAnswer1->isChecked());
    _answer2.setDescription(ui->answer2->toPlainText());
    _answer2.setIsCorrectAnswer(ui->correctAnswer2->isChecked());
    _answer3.setDescription(ui->answer3->toPlainText());
    _answer3.setIsCorrectAnswer(ui->correctAnswer3->isChecked());
    _answer4.setDescription(ui->answer4->toPlainText());
    _answer4.setIsCorrectAnswer(ui->correctAnswer4->isChecked());
    _model.setAnswers(QList<Answer>());
    _model.addAnswer(_answer1);
    _model.addAnswer(_answer2);
    _model.addAnswer(_answer3);
    _model.addAnswer(_answer4);
    DAOQuestion *daoQuestion = new DAOQuestionSQLITE;
    return (daoQuestion->addOrUpdateQuestion(&_model));
}

void NewQuestionWindow::on_saveAndContinueButton_clicked()
{
    if(saveQuestion()){
        _model = Question();
        ui->answer1->clear();
        ui->answer2->clear();
        ui->answer3->clear();
        ui->answer4->clear();
        ui->question->clear();
    }

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
