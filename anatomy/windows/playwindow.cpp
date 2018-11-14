#include "playwindow.h"
#include "ui_playwindow.h"

#include "DAO/daoassignmentsqlite.h"

PlayWindow::PlayWindow(int assignmentId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);

    DAOAssignment *daoAssignmet = new DAOAssignmentSQLITE;
    _assignment = daoAssignmet->getAssignmentById(assignmentId);

    foreach (AnatomyImage anatomyimage, _assignment.anatomyImageList()) {
       images.append(QPixmap(qApp->applicationDirPath()+"/"+anatomyimage.imagePath()));
    }
    QPixmap map(qApp->applicationDirPath()+"/images/coluna/AP.png"); // use qradiobutton in a qbuttongroup or a qcombobox.
    ui->image->setScaledContents(true);
    ui->image->setPixmap(map);
    ui->image->show();
    currentImageIndex = 0;
}

PlayWindow::~PlayWindow()
{
    delete ui;
}

void PlayWindow::on_rightArrowButton_clicked()
{
    if(currentImageIndex<images.size()-1)
        ui->image->setPixmap(images[++currentImageIndex]);
}

void PlayWindow::on_leftArrowButton_clicked()
{
    if(currentImageIndex>0)
        ui->image->setPixmap(images[--currentImageIndex]);
}
