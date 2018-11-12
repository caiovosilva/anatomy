#include "playwindow.h"
#include "ui_playwindow.h"

#include <QPixmap>

#include "DAO/daoassignmentsqlite.h"

PlayWindow::PlayWindow(int assignmentId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);

    DAOAssignment *daoAssignmet = new DAOAssignmentSQLITE;
    _assignment = daoAssignmet->getAssignmentById(assignmentId);

    QPixmap map(qApp->applicationDirPath()+"/images/coluna/AP.png"); // use qradiobutton in a qbuttongroup or a qcombobox.
    ui->image->setPixmap(map);
    ui->image->show();
}

PlayWindow::~PlayWindow()
{
    delete ui;
}
