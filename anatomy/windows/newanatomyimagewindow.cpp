#include "newanatomyimagewindow.h"
#include "ui_newanatomyimagewindow.h"

NewAnatomyImageWindow::NewAnatomyImageWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAnatomyImageWindow)
{
    ui->setupUi(this);

    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        ui->modalityComboBox->addItem(item.getDescription(), item.getId());
    }
}

NewAnatomyImageWindow::~NewAnatomyImageWindow()
{
    delete ui;
}

void NewAnatomyImageWindow::on_modalityComboBox_currentIndexChanged(int index)
{
    int modalityId = ui->modalityComboBox->currentData().toInt();

    QList<AnatomicalRegion> anatomicalRegionList;
    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE;
    anatomicalRegionList = daoAnatomicalRegion->getAnatomicalRegionByModalityId(modalityId);

    ui->anatomicalRegionComboBox->clear();
    foreach (AnatomicalRegion item, anatomicalRegionList) {
        ui->anatomicalRegionComboBox->addItem(item.getDescription(), item.getId());
    }
}
