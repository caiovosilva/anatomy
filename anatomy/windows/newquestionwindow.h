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
//    void on_buttonBox_accepted();
//    void on_buttonBox_rejected();

    void on_cancelButton_clicked();

    void on_saveButton_clicked();

    void on_saveAndContinueButton_clicked();

    void on_modalitiesComboBox_currentIndexChanged(int index);

    void on_anatomicalRegionComboBox_currentIndexChanged(int index);

private:
    void saveQuestion();
    bool oneCorrectAnswerSelected();
    bool allAnswersAndQuestionFilled();
    Ui::NewQuestionWindow *ui;
};

#endif // NEWQUESTIONWINDOW_H
