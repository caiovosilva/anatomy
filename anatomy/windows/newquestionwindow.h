#ifndef NEWQUESTIONWINDOW_H
#define NEWQUESTIONWINDOW_H

#include <QWidget>
#include "model/question.h"

namespace Ui {
class NewQuestionWindow;
}

class NewQuestionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewQuestionWindow(Question *model = nullptr, QWidget *parent = 0);
    ~NewQuestionWindow();

private slots:
    void on_cancelButton_clicked();
    void on_saveButton_clicked();
    void on_saveAndContinueButton_clicked();
    void on_modalitiesComboBox_currentIndexChanged(int index);
    void on_anatomicalRegionComboBox_currentIndexChanged(int index);

private:
    Ui::NewQuestionWindow *ui;
    bool saveQuestion();
    bool oneCorrectAnswerSelected();
    bool allAnswersAndQuestionFilled();
    Question _model;
    Answer _answer1;
    Answer _answer2;
    Answer _answer3;
    Answer _answer4;
};

#endif // NEWQUESTIONWINDOW_H
