#include "newanatomicalregionwindow.h"
#include "ui_newanatomicalregionwindow.h"

#include <QMessageBox>

NewAnatomicalRegionWindow::NewAnatomicalRegionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAnatomicalRegionWindow)
{
    ui->setupUi(this);

    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        ui->modalitiesComboBox->addItem(item.description(), item.id());
    }

}

NewAnatomicalRegionWindow::~NewAnatomicalRegionWindow()
{
    delete ui;
}

void NewAnatomicalRegionWindow::on_saveButton_clicked()
{
    QString description = ui->descriptionText->toPlainText();
    if(description.isEmpty())
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Preencha o campo de descrição!");
        msg.exec();
        return;
    }
    int modalityId = ui->modalitiesComboBox->currentData().toInt();

    AnatomicalRegion anatomicalRegion;
    anatomicalRegion.setModalityId(modalityId);
    anatomicalRegion.setDescription(description);

    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE;
    bool result = daoAnatomicalRegion->addAnatomicalRegion(&anatomicalRegion);

    if(!result)
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Erro ao adicionar nova Modalidade!");
        msg.exec();
        return;
    }
    this->close();
}
