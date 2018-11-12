#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QWidget>

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

private:
    Ui::PlayWindow *ui;
    Assignment _assignment;
};

#endif // PLAYWINDOW_H
