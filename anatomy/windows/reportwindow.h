#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QWidget>
#include <QString>

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
    void on_saveButton_clicked();

private:
    Ui::ReportWindow *ui;
    QString _text;
};

#endif // REPORTWINDOW_H
