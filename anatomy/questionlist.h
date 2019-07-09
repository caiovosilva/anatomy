#ifndef QUESTIONLIST_H
#define QUESTIONLIST_H

#include <QWidget>
#include <QtWidgets>
#include <QIcon>
#include <QDesktopWidget>
#include "model/questionmodel.h"

namespace Ui {
class QuestionList;
}

class QuestionList : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionList(QWidget *parent = nullptr);
    ~QuestionList();

private:

public slots:
    void editItem(QModelIndex model);

private slots:
    void on_modalitiesComboBox_currentIndexChanged(int index);

    void on_anatomicalRegionComboBox_currentIndexChanged(int index);

    void on_addNewQuestionButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::QuestionList *ui;
    //void fillTable();
    //QGridLayout _layout{this};
    QTableView *_view;
    QPushButton *_btnAddItem;
    QPushButton *_btnDeleteItem;
    QuestionModel _model;
    QSortFilterProxyModel _proxy;
    QInputDialog _dialog;

};

#endif // QUESTIONLIST_H
