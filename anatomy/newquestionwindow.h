#ifndef NEWQUESTIONWINDOW_H
#define NEWQUESTIONWINDOW_H

#include <QWidget>

namespace Ui {
class NewQuestionWindow;
}

class NewQuestionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewQuestionWindow(QWidget *parent = 0);
    ~NewQuestionWindow();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    bool oneCorrectAnswerSelected();
    bool allAnswersAndQuestionFilled();
    Ui::NewQuestionWindow *ui;
};

#endif // NEWQUESTIONWINDOW_H
