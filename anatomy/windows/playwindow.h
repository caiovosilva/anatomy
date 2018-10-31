#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QWidget>

#include "model/anatomyimage.h"

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlayWindow(AnatomyImage anatomyImage, QWidget *parent = 0);
    ~PlayWindow();

private:
    Ui::PlayWindow *ui;
    AnatomyImage _anatomyImage;
};

#endif // PLAYWINDOW_H
