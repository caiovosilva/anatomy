#include "newmodalitywindow.h"
#include "ui_newmodalitywindow.h"

#include <QMessageBox>

#include "DAO/daomodalitysqlite.h"

NewModalityWindow::NewModalityWindow(Modality *modality, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewModalityWindow),
    _modality(modality)
{
    ui->setupUi(this);
    setWindowTitle("Nova Modalidade");
    if(_modality != nullptr)
        ui->descriptionText->setText(_modality->description());
    else
        _modality = new Modality();

}

//NewModalityWindow::NewModalityWindow(Modality *modality, QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::NewModalityWindow),
//    _modality(modality)
//{
//    NewModalityWindow();
//}

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
    //Modality modality = Modality(description);
    _modality->setDescription(description);
    DAOModality *daoModality = new DAOModalitySQLITE;
    bool result = daoModality->addOrUpdateModality(_modality);

    if(!result)
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Erro ao adicionar nova Modalidade!");
        msg.exec();
        return;
    }

    delete _modality;
    delete daoModality;
    this->close();
}
