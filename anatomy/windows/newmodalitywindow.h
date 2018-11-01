#ifndef NEWMODALITYWINDOW_H
#define NEWMODALITYWINDOW_H

#include <QWidget>

namespace Ui {
class NewModalityWindow;
}

class NewModalityWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewModalityWindow(QWidget *parent = 0);
    ~NewModalityWindow();

private slots:
    void on_saveButton_clicked();

private:
    Ui::NewModalityWindow *ui;
};

#endif // NEWMODALITYWINDOW_H
