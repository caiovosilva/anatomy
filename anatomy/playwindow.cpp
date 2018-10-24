#include "playwindow.h"
#include "ui_playwindow.h"

#include <QPixmap>

PlayWindow::PlayWindow(AnatomyImage anatomyImage, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayWindow),
    _anatomyImage(anatomyImage)
{
    ui->setupUi(this);

    QPixmap map(qApp->applicationDirPath()+"/images/coluna/AP.png"); // use qradiobutton in a qbuttongroup or a qcombobox.
    ui->image->setPixmap(map);
    ui->image->show();
}

PlayWindow::~PlayWindow()
{
    delete ui;
}
