#include "playwindow.h"
#include "ui_playwindow.h"

PlayWindow::PlayWindow(int assignmentId, QString studentName, QWidget *parent) :
    _studentName(studentName),
    QWidget(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);

    DAOAssignment *daoAssignmet = new DAOAssignmentSQLITE;
    _assignment = daoAssignmet->getAssignmentById(assignmentId);

    foreach (AnatomyImage anatomyimage, _assignment.anatomyImageList()) {
       _images.append(QPixmap(qApp->applicationDirPath()+"/"+anatomyimage.imagePath()));
    }
    QPixmap map(qApp->applicationDirPath()+"/images/coluna/AP.png"); // use qradiobutton in a qbuttongroup or a qcombobox.
    ui->image->setScaledContents(true);
    ui->image->setPixmap(map);
    ui->image->show();
    _currentImageIndex = 0;
    fillQuestions();
    _startTime = QTime::currentTime();
}

PlayWindow::~PlayWindow()
{
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
    QGridLayout *grid = new QGridLayout;

    foreach (Question item, _assignment.questionsList()) {
        QButtonGroup *buttonGroup = new QButtonGroup;
        QGroupBox *groupBox = new QGroupBox(item.description());
        QHBoxLayout *hbox = new QHBoxLayout;

        foreach (Answer answer, item.answers())
        {
            QRadioButton *aws = new QRadioButton(answer.description());
            buttonGroup->addButton(aws, answer.id());
            hbox->addWidget(aws);
        }
        groupBox->setLayout(hbox);
        grid->addWidget(groupBox,line++, column);
        _answers.append(buttonGroup);
    }

    QWidget *client = new QWidget;
    ui->questionsScrollArea->setWidgetResizable(true);
    ui->questionsScrollArea->setWidget(client);
    client->setLayout(grid);
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
    newWindow->setWindowTitle("Relatório");
    newWindow->show();
    this->close();
}

void PlayWindow::on_buttonBox_rejected()
{
    this->close();
}
