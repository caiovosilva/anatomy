#ifndef ASSIGNMENTLIST_H
#define ASSIGNMENTLIST_H


#include <QWidget>
#include <QtWidgets>
#include <QIcon>
#include <QDesktopWidget>
#include "model/assignmentmodel.h"

namespace Ui {
class AssignmentList;
}

class AssignmentList : public QWidget
{
    Q_OBJECT

public:
    explicit AssignmentList(QWidget *parent = nullptr);
    ~AssignmentList();

public slots:
    void newItem();
    void editItem(QModelIndex model);
    void onDeleteItem();

private:
    Ui::AssignmentList *ui;
    void fillTable();
    QGridLayout _layout{this};
    QTableView _view;
    QPushButton _btnAddItem{"Adicionar Nova Tarefa"};
    QPushButton _btnDeleteItem{"Apagar"};
    AssignmentModel _model;
    QSortFilterProxyModel _proxy;
    QInputDialog _dialog;
};

#endif // ASSIGNMENTLIST_H
