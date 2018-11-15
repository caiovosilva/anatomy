#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>
#include <QMessageBox>

#include "model/assignment.h"

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlayWindow(int assignmentId, QWidget *parent = 0);
    ~PlayWindow();

private slots:
    void on_rightArrowButton_clicked();
    void on_leftArrowButton_clicked();
    void on_buttonBox_accepted();

private:
    Ui::PlayWindow *ui;
    Assignment _assignment;
    QList<QPixmap> _images;
    int _currentImageIndex;
    QList<QButtonGroup*> _answers;
    void fillQuestions();
};

#endif // PLAYWINDOW_H
