#ifndef NEWANATOMICALREGIONWINDOW_H
#define NEWANATOMICALREGIONWINDOW_H

#include <QWidget>

#include "DAO/daomodality.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoanatomicalregion.h"
#include "DAO/daoanatomicalregionsqlite.h"

namespace Ui {
class NewAnatomicalRegionWindow;
}

class NewAnatomicalRegionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewAnatomicalRegionWindow(AnatomicalRegion *anatomicalRegion = nullptr, QWidget *parent = 0);
    ~NewAnatomicalRegionWindow();

private slots:
    void on_saveButton_clicked();

private:
    Ui::NewAnatomicalRegionWindow *ui;
    AnatomicalRegion _anatomicalRegion;
};

#endif // NEWANATOMICALREGIONWINDOW_H
