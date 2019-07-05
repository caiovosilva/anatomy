#ifndef ANATOMICALREGIONLIST_H
#define ANATOMICALREGIONLIST_H

#include <QWidget>
#include <QtWidgets>
#include <QIcon>
#include <QDesktopWidget>
#include "model/anatomicalregionmodel.h"

namespace Ui {
class AnatomicalRegionList;
}

class AnatomicalRegionList : public QWidget
{
    Q_OBJECT

public:
    explicit AnatomicalRegionList(QWidget *parent = nullptr);
    ~AnatomicalRegionList();

public slots:
    void newModalityButtonClicked();
    void editModality(QModelIndex model);
    void onDeleteModality();

private:
    Ui::AnatomicalRegionList *ui;
    void fillTable();
    QGridLayout _layout{this};
    QTableView _view;
    QPushButton _btnAddModality{"Adicionar Nova Modalidade"};
    QPushButton _btnDeleteModality{"Apagar"};
    AnatomicalRegionModel _model;
    QSortFilterProxyModel _proxy;
    QInputDialog _dialog;
};

#endif // ANATOMICALREGIONLIST_H
