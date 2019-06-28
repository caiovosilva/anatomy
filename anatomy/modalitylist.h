#ifndef MODALITYLIST_H
#define MODALITYLIST_H

#include <QWidget>
#include <QtWidgets>
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

private:
    void fillTable();
    Ui::ModalityList *ui;
    QGridLayout m_layout{this};
    QTableView m_view;
    QPushButton m_button{"Adicionar Nova Modalidade"};
    ModalityModel m_model;
    QSortFilterProxyModel m_proxy;
    QInputDialog m_dialog;
};

#endif // MODALITYLIST_H
