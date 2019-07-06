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
    void newItem();
    void editItem(QModelIndex model);
    void onDeleteItem();

private:
    Ui::AnatomicalRegionList *ui;
    void fillTable();
    QGridLayout _layout{this};
    QTableView _view;
    QPushButton _btnAddItem{"Adicionar Nova Modalidade"};
    QPushButton _btnDeleteItem{"Apagar"};
    AnatomicalRegionModel _model;
    QSortFilterProxyModel _proxy;
    QInputDialog _dialog;
};

#endif // ANATOMICALREGIONLIST_H
