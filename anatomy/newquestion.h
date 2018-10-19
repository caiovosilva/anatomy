#ifndef NEWQUESTION_H
#define NEWQUESTION_H

#include <QDialog>
#include <QRadioButton>

namespace Ui {
class NewQuestion;
}

class NewQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit NewQuestion(QWidget *parent = 0);
    ~NewQuestion();

private slots:
    void on_buttonBox_accepted();

private:
    bool oneCorrectAnswerSelected();
    QList<QRadioButton> answerButtons;
    Ui::NewQuestion *ui;
};

#endif // NEWQUESTION_H
