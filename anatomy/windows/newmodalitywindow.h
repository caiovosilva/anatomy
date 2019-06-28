#ifndef NEWMODALITYWINDOW_H
#define NEWMODALITYWINDOW_H

#include <QWidget>
#include "model/modality.h"

namespace Ui {
class NewModalityWindow;
}

class NewModalityWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewModalityWindow(Modality *_modality = nullptr, QWidget *parent = 0);
    //explicit NewModalityWindow(Modality *_modality, QWidget *parent = 0);
    ~NewModalityWindow();

private slots:
    void on_saveButton_clicked();

private:
    Ui::NewModalityWindow *ui;
    Modality _modality;
};

#endif // NEWMODALITYWINDOW_H
