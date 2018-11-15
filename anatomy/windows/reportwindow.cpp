#include "reportwindow.h"
#include "ui_reportwindow.h"

#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

ReportWindow::ReportWindow(QString text, QWidget *parent) :
    QWidget(parent),
    _text(text),
    ui(new Ui::ReportWindow)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *textLabel = new QLabel(text);
    layout->addWidget(textLabel);
    QWidget *widget = new QWidget;
    ui->textArea->setWidgetResizable(true);
    ui->textArea->setWidget(widget);
    widget->setLayout(layout);
}

ReportWindow::~ReportWindow()
{
    delete ui;
}

void ReportWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Salvar Relatório"), "",
            tr("Text File (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
            return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << _text;
    }
}
