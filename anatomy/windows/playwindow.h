#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>
#include <QMessageBox>
#include <QDateTime>
#include <QTime>

#include "DAO/daoassignmentsqlite.h"
#include "reportwindow.h"
#include "model/assignment.h"

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlayWindow(int assignmentId, QString studentName, QWidget *parent = 0);
    ~PlayWindow();

private slots:
    void on_rightArrowButton_clicked();
    void on_leftArrowButton_clicked();
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::PlayWindow *ui;
    Assignment _assignment;
    QList<QPixmap> _images;
    int _currentImageIndex;
    QList<QButtonGroup*> _answers;
    QString _studentName;
    void fillQuestions();
    QTime _startTime;
};

#endif // PLAYWINDOW_H
