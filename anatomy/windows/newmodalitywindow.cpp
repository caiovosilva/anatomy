#include "newmodalitywindow.h"
#include "ui_newmodalitywindow.h"

#include "model/modality.h"
#include "DAO/daomodalitysqlite.h"

NewModalityWindow::NewModalityWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewModalityWindow)
{
    ui->setupUi(this);
}

NewModalityWindow::~NewModalityWindow()
{
    delete ui;
}

void NewModalityWindow::on_saveButton_clicked()
{
    Modality modality = Modality(ui->descriptionText->toPlainText());

    DAOModality *daoModality = new DAOModalitySQLITE;
    daoModality->addModality(&modality);

    this->close();
}
