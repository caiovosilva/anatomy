#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QWidget>
#include <QPixmap>

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

private:
    Ui::PlayWindow *ui;
    Assignment _assignment;
    QList<QPixmap> images;
    int currentImageIndex;
};

#endif // PLAYWINDOW_H
