#include "playwindow.h"
#include "ui_playwindow.h"
#include <QGuiApplication>
#include <QScreen>

PlayWindow::PlayWindow(int assignmentId, QString studentName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayWindow),
    _studentName(studentName)
{
    ui->setupUi(this);
    resize(QGuiApplication::primaryScreen()->size());

    DAOAssignment *daoAssignmet = new DAOAssignmentSQLITE;
    _assignment = daoAssignmet->getAssignmentById(assignmentId);

    foreach (AnatomyImage anatomyimage, _assignment.anatomyImageList()) {
        QPixmap outPixmap = QPixmap();
        outPixmap.loadFromData(anatomyimage.image());
       _images.append(outPixmap);
    }
    ui->image->setScaledContents(true);
    ui->image->setPixmap(_images[0]);
    ui->image->show();
    _currentImageIndex = 0;
    fillQuestions();
    _startTime = QTime::currentTime();

    delete daoAssignmet;
}

PlayWindow::~PlayWindow()
{
    delete _grid;
    delete ui;
}

void PlayWindow::on_rightArrowButton_clicked()
{
    if(_currentImageIndex<_images.size()-1)
        ui->image->setPixmap(_images[++_currentImageIndex]);
}

void PlayWindow::on_leftArrowButton_clicked()
{
    if(_currentImageIndex>0)
        ui->image->setPixmap(_images[--_currentImageIndex]);
}

void PlayWindow::fillQuestions()
{
    int line =0;
    int column = 0;
    _grid = new QGridLayout;

    foreach (Question item, _assignment.questionsList()) {
        _buttonGroup = new QButtonGroup;
        _groupBox = new QGroupBox(item.description());
        _hbox = new QHBoxLayout;

        foreach (Answer answer, item.answers())
        {
            QRadioButton *aws = new QRadioButton(answer.description());
            _buttonGroup->addButton(aws, answer.id());
            _hbox->addWidget(aws);
        }
        _groupBox->setLayout(_hbox);
        _grid->addWidget(_groupBox,line++, column);
        _answers.append(_buttonGroup);
    }

    QWidget *client = new QWidget;
    ui->questionsScrollArea->setWidgetResizable(true);
    ui->questionsScrollArea->setWidget(client);
    client->setLayout(_grid);
}

void PlayWindow::on_buttonBox_accepted()
{
    for (int i = 0; i < _answers.size(); i++)
    {
        if(_answers[i]->checkedId()<0)
        {
            QMessageBox msg(QMessageBox::Critical, "Erro", "Responda todas as perguntas!");
            msg.exec();
            return;
        }
    }
    QString result;
    int correctAnswers = 0;
    QDateTime dateTime = QDateTime::currentDateTime();
    result = "Aluno: " + _studentName+"\n";
    result += "Tarefa: " + _assignment.description()+"\n";
    result += "Data: " + dateTime.date().toString("dd/MM/yyyy")+"\n";
    result += "Horário: " + dateTime.time().toString("HH:mm")+"\n";
    int secondsToFinish = _startTime.secsTo(dateTime.time());
    QTime timer(0,0,secondsToFinish);
    result += "Tempo necessário: " + timer.toString("HH:mm:ss")+"\n";
    QList<Question> questions = _assignment.questionsList();
    Answer correctAnswer;
    for (int i = 0; i < _answers.size(); i++)
    {
        foreach (Answer aws, questions[i].answers())
            if(aws.isCorrectAnswer())
                correctAnswer = aws;
        if(correctAnswer.id()==_answers[i]->checkedId())
        {
            result += "Ponto "+questions[i].description()+ " Correto.\n";
            correctAnswers++;
        }
        else
            result += "Ponto "+questions[i].description()+ " Errado! A resposta certa é "+correctAnswer.description()+".\n";
    }

    result += "Você acertou "+QString::number(correctAnswers)+" de "+QString::number(questions.size())+" perguntas.";

    ReportWindow *newWindow = new ReportWindow(result);
    newWindow->show();
    this->close();
}

void PlayWindow::on_buttonBox_rejected()
{
    this->close();
}
