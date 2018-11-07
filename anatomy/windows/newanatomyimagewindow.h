#ifndef NEWANATOMYIMAGEWINDOW_H
#define NEWANATOMYIMAGEWINDOW_H

#include <QWidget>

#include "DAO/daomodality.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoanatomicalregion.h"
#include "DAO/daoanatomicalregionsqlite.h"


namespace Ui {
class NewAnatomyImageWindow;
}

class NewAnatomyImageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewAnatomyImageWindow(QWidget *parent = 0);
    ~NewAnatomyImageWindow();

private slots:
    void on_modalityComboBox_currentIndexChanged(int index);

private:
    Ui::NewAnatomyImageWindow *ui;
};

#endif // NEWANATOMYIMAGEWINDOW_H
