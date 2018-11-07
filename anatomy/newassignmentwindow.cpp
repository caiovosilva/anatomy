#include "newassignmentwindow.h"
#include "ui_newassignmentwindow.h"

#include <QFileDialog>

NewAssignmentWindow::NewAssignmentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAssignmentWindow)
{
    ui->setupUi(this);

    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        ui->modalityComboBox->addItem(item.getDescription(), item.getId());
    }
}

NewAssignmentWindow::~NewAssignmentWindow()
{
    delete ui;
}

void NewAssignmentWindow::on_findFileButton_clicked()
{
    anatomyImagesPath = QFileDialog::getOpenFileNames(this, tr("Escolha Imagens"),
                                                          qApp->applicationDirPath()+"/images",
                                                          "Image Files (*.png *.jpg *.bmp)");
    QDir dir(qApp->applicationDirPath());
    for( int i=0; i<anatomyImagesPath.size(); i++)
    {
        anatomyImagesPath[i] =  dir.relativeFilePath(anatomyImagesPath[i]);
    }
}

void NewAssignmentWindow::on_modalityComboBox_currentIndexChanged(int index)
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
