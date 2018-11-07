#include "newanatomyimagewindow.h"
#include "ui_newanatomyimagewindow.h"

NewAnatomyImageWindow::NewAnatomyImageWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAnatomyImageWindow)
{
    ui->setupUi(this);


}

NewAnatomyImageWindow::~NewAnatomyImageWindow()
{
    delete ui;
}

void NewAnatomyImageWindow::on_modalityComboBox_currentIndexChanged(int index)
{

}
