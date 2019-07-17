#ifndef MODALITYLIST_H
#define MODALITYLIST_H

#include <QWidget>
#include <QtWidgets>
#include <QIcon>
#include <QDesktopWidget>
#include "model/modalitymodel.h"

namespace Ui {
class ModalityList;
}

class ModalityList : public QWidget
{
    Q_OBJECT

public:
    explicit ModalityList(QWidget *parent = nullptr);
    ~ModalityList();

public slots:
    void newModalityButtonClicked();
    void editModality(QModelIndex model);
    void onDeleteModality();
private:
    void fillTable();
    Ui::ModalityList *ui;
    QGridLayout _layout{this};
    QTableView _view;
    QPushButton _btnAddModality{"Adicionar Nova Modalidade"};
    QPushButton _btnDeleteModality{"Apagar"};
    ModalityModel _model;
    QSortFilterProxyModel _proxy;
    QInputDialog _dialog;
};

#endif // MODALITYLIST_H
