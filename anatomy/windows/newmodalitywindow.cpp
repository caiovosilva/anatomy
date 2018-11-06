#include "newmodalitywindow.h"
#include "ui_newmodalitywindow.h"

#include <QMessageBox>

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
    QString description = ui->descriptionText->toPlainText();
    if(description.isEmpty())
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Preencha o campo de descrição!");
        msg.exec();
        return;
    }
    Modality modality = Modality(description);

    DAOModality *daoModality = new DAOModalitySQLITE;
    bool result = daoModality->addModality(&modality);

    if(!result)
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Erro ao adicionar nova Modalidade!");
        msg.exec();
        return;
    }
    this->close();
}
