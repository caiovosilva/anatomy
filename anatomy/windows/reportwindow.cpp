#include "reportwindow.h"
#include "ui_reportwindow.h"


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

void ReportWindow::on_saveButtonTxt_clicked()
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

void ReportWindow::on_pushButtonPdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setPlainText(_text);
    doc.setPageSize(printer.pageRect().size());
    doc.print(&printer);
}
