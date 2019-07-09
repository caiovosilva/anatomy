#include "newanatomicalregionwindow.h"
#include "ui_newanatomicalregionwindow.h"

#include <QMessageBox>

NewAnatomicalRegionWindow::NewAnatomicalRegionWindow(AnatomicalRegion *anatomicalRegion, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAnatomicalRegionWindow)
{
    ui->setupUi(this);
    setWindowTitle("Nova Região Anatômica");

    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();
    foreach (Modality item, modalitiesList) {
        ui->modalitiesComboBox->addItem(item.description(), item.id());
    }

    if(anatomicalRegion != nullptr) {
        QString description = anatomicalRegion->description();
        _anatomicalRegion.setId(anatomicalRegion->id());
        _anatomicalRegion.setModalityId(anatomicalRegion->modalityId());
        _anatomicalRegion.setDescription(description);
        ui->descriptionText->setText(description);
        int index = ui->modalitiesComboBox->findData(anatomicalRegion->modalityId());
        if ( index != -1 )
            ui->modalitiesComboBox->setCurrentIndex(index);
    }

    delete daoModality;
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

    _anatomicalRegion.setModalityId(modalityId);
    _anatomicalRegion.setDescription(description);
    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE;
    bool result = daoAnatomicalRegion->addOrUpdateAnatomicalRegion(&_anatomicalRegion);

    if(!result)
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Erro ao adicionar nova Modalidade!");
        msg.exec();
        return;
    }

    delete daoAnatomicalRegion;
    this->close();
}
