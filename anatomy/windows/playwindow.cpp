#include "playwindow.h"
#include "ui_playwindow.h"
#include <QGuiApplication>
#include <QScreen>
#include <random>

PlayWindow::PlayWindow(int assignmentId, QString studentName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayWindow),
    _studentName(studentName)
{
    ui->setupUi(this);
    setWindowTitle("Tarefa");
    //resize(size);
    showMaximized();
    ui->questionsScrollArea->setMinimumSize(0,QGuiApplication::primaryScreen()->size().rheight()-170);

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
    ui->assignmentLabel->setText(_assignment.description());
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
    int line = 0;
    int column = 0;
    int questiosIndex = 1;
    _grid = new QGridLayout;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator

    foreach (Question item, _assignment.questionsList()) {
        QString options[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
        int optionsIndex = 0;
        _buttonGroup = new QButtonGroup;
        _groupBox = new QGroupBox("Questão " + item.description());
        _hbox = new QHBoxLayout;
        QList<Answer> answers = item.answers();
        questiosIndex++;

        while (answers.size()>0) {
            int index = std::uniform_int_distribution<>(0, answers.size()-1)(eng);
            QRadioButton *aws = new QRadioButton(options[optionsIndex]+ ") " + answers[index].description());
            _buttonGroup->addButton(aws, answers[index].id());
            _hbox->addWidget(aws);
            answers.removeAt(index);
            optionsIndex++;
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
            result += "Questão "+questions[i].description()+ " Correta.\n";
            correctAnswers++;
        }
        else
            result += "Questão "+questions[i].description()+ " Errada! A resposta certa é "+correctAnswer.description()+".\n";
    }

    result += "Você acertou "+QString::number(correctAnswers)+" de "+QString::number(questions.size())+" questões.";

    ReportWindow *newWindow = new ReportWindow(result);
    newWindow->show();
    this->close();
}

void PlayWindow::on_buttonBox_rejected()
{
    this->close();
}
