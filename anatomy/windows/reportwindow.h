#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QWidget>
#include <QString>
#include <QPrinter>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextDocument>


namespace Ui {
class ReportWindow;
}

class ReportWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReportWindow(QString text, QWidget *parent = 0);
    ~ReportWindow();

private slots:

    void on_saveButtonTxt_clicked();

    void on_pushButtonPdf_clicked();

private:
    Ui::ReportWindow *ui;
    QString _text;
};

#endif // REPORTWINDOW_H
