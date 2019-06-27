#include "newassignmentwindow.h"
#include "ui_newassignmentwindow.h"

#include <QFileDialog>
#include <QMessageBox>

NewAssignmentWindow::NewAssignmentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAssignmentWindow)
{
    ui->setupUi(this);
    setWindowTitle("Nova Tarefa");

    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        ui->modalityComboBox->addItem(item.description(), item.id());
    }

    delete daoModality;
}

NewAssignmentWindow::~NewAssignmentWindow()
{
    delete ui;
}

void NewAssignmentWindow::on_findFileButton_clicked()
{
    QString applicationDirPath = qApp->applicationDirPath();
    anatomyImagesPath = QFileDialog::getOpenFileNames(this, tr("Selecione as Imagens"),
                                                          applicationDirPath+"/images",
                                                          "Image Files (*.png)");
//    QDir dir(applicationDirPath);
//    for( int i=0; i<anatomyImagesPath.size(); i++)
//    {
//        anatomyImagesPath[i] =  dir.relativeFilePath(anatomyImagesPath[i]);
//    }
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

    delete daoAnatomicalRegion;
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
        QPixmap inPixmap = QPixmap(anatomyImagesPath[i]);
        QByteArray inByteArray;
        QBuffer inBuffer( &inByteArray );
        inBuffer.open( QIODevice::WriteOnly );
        inPixmap.save( &inBuffer, "PNG" ); // write inPixmap into inByteArray in PNG format
        AnatomyImage anatomyImage(inByteArray, assignmentId);
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
