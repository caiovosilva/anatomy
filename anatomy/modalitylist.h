#ifndef MODALITYLIST_H
#define MODALITYLIST_H

#include <QMainWindow>
#include <QtWidgets>
#include <QDesktopWidget>
#include "model/modalitymodel.h"

namespace Ui {
class modalityList;
}

class modalityList : public QMainWindow
{
    Q_OBJECT

public:
    explicit modalityList(QWidget *parent = nullptr);
    ~modalityList();
    void Widget();

private:
    Ui::modalityList *ui;
    QGridLayout m_layout{this};
    QTableView m_view;
    QPushButton m_button{"Filter"};
    ModalityModel m_model;
    QSortFilterProxyModel m_proxy;
    QInputDialog m_dialog;
};

#endif // MODALITYLIST_H
