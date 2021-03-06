#include "newassignmentwindow.h"
#include "ui_newassignmentwindow.h"

#include <QFileDialog>
#include <QMessageBox>

NewAssignmentWindow::NewAssignmentWindow(Assignment *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAssignmentWindow)
{
    ui->setupUi(this);
    setWindowTitle("Tarefa");

    if(model != nullptr) {
        QString description = model->description();
        _model.setId(model->id());
        _model.setAnatomicalRegionId(model->anatomicalRegionId());
        _model.setDescription(description);
        _model.setAnatomyImageList(model->anatomyImageList());
        ui->descriptionText->setText(description);
    }

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
    _model.setDescription(ui->descriptionText->toPlainText());
    _model.setAnatomicalRegionId(anatomicalRegionId);
    QList<AnatomyImage> oldImages;
    if(anatomyImagesPath.size()>0 && _model.anatomyImageList().size()>0)
    {
        oldImages = _model.anatomyImageList();
        _model.setAnatomyImageList(QList<AnatomyImage>());
    }
    for( int i=0; i<anatomyImagesPath.size(); i++)
    {
        QPixmap inPixmap = QPixmap(anatomyImagesPath[i]);
        QByteArray inByteArray;
        QBuffer inBuffer( &inByteArray );
        inBuffer.open( QIODevice::WriteOnly );
        inPixmap.save( &inBuffer, "PNG" ); // write inPixmap into inByteArray in PNG format
        _model.addnatomyImage(AnatomyImage(inByteArray));
    }
    if(_model.anatomyImageList().size()<1)
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Selecione pelo menos uma imagem!");
        msg.exec();
        return;
    }
    DAOAssignment *daoAssignment = new DAOAssignmentSQLITE;
    if(daoAssignment->addOrUpdateAssignment(&_model))
    {
        DAOAnatomyImage *daoAnatomyImage = new DAOAnatomyImageSQLITE;
        foreach (AnatomyImage item, oldImages)
            daoAnatomyImage->deleteAnatomyImage(item.id());
    }
    else
    {
        QMessageBox msg(QMessageBox::Critical, "Erro", "Ocorreu um erro ao adicionar tarefa!");
        msg.exec();
        return;
    }

    this->close();
}
