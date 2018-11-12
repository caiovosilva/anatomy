#include "newassignmentwindow.h"
#include "ui_newassignmentwindow.h"

#include <QFileDialog>
#include <QMessageBox>

NewAssignmentWindow::NewAssignmentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAssignmentWindow)
{
    ui->setupUi(this);

    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        ui->modalityComboBox->addItem(item.description(), item.id());
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
        QString aaaa = dir.relativeFilePath(anatomyImagesPath[i]);
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
        ui->anatomicalRegionComboBox->addItem(item.description(), item.id());
    }
}

void NewAssignmentWindow::on_saveButton_clicked()
{
    int anatomicalRegionId = ui->anatomicalRegionComboBox->currentData().toInt();
    Assignment assignment = Assignment(ui->descriptionText->toPlainText(), anatomicalRegionId);

    DAOAssignment *daoAssignment = new DAOAssignmentSQLITE;
    bool result = daoAssignment->addAssignment(&assignment);

    int assignmentId =  assignment.id();
    DAOAnatomyImage *daoAnatomyImage = new DAOAnatomyImageSQLITE;
    for( int i=0; i<anatomyImagesPath.size(); i++)
    {
        AnatomyImage anatomyImage(anatomyImagesPath[i], assignmentId);
        result = result && daoAnatomyImage->addAnatomyImage(&anatomyImage);
    }

    if(!result)
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Ocorreu um erro ao adicionar tarefa!");
        msg.exec();
        return;
    }
    this->close();

}