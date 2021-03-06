#include "assignmentlist.h"
#include "ui_assignmentlist.h"

#include "DAO/daoassignmentsqlite.h"
#include "windows/newassignmentwindow.h"

AssignmentList::AssignmentList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssignmentList)
{
    ui->setupUi(this);
    this->setWindowTitle("Tarefas");

    QPalette pal = _btnDeleteItem.palette();
    pal.setColor(QPalette::Button, QColor(Qt::red));
    _btnDeleteItem.setAutoFillBackground(true);
    _btnDeleteItem.setPalette(pal);
    _btnDeleteItem.update();
    QPalette pal2 = _btnAddItem.palette();
    pal2.setColor(QPalette::Button, QColor(Qt::green));
    _btnAddItem.setAutoFillBackground(true);
    _btnAddItem.setPalette(pal2);
    _btnAddItem.update();

    _layout.addWidget(&_view, 0, 0, 1, 1);
    _layout.addWidget(&_btnAddItem, 1, 0, 1, 1);
    _layout.addWidget(&_btnDeleteItem, 2, 0, 1, 1);
    connect(&_btnAddItem, SIGNAL(clicked()), this, SLOT(newItem()));
    connect(&_btnDeleteItem, SIGNAL(clicked()), this, SLOT(onDeleteItem()));
    fillTable();
    _proxy.setSourceModel(&_model);
    _view.setModel(&_proxy);
    _view.resizeColumnsToContents();
    _view.setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(&_view, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(editItem(QModelIndex)));
}

AssignmentList::~AssignmentList()
{
    delete ui;
}

void AssignmentList::fillTable()
{
    DAOAssignment *dao = new DAOAssignmentSQLITE;
    QList<Assignment> assignmentList = dao->getAllAssignments();

    foreach (Assignment item, assignmentList) {
        _model.append(item);
    }

    delete dao;
}

void AssignmentList::newItem()
{
    NewAssignmentWindow *newWindow = new NewAssignmentWindow;
    newWindow->show();
    this->close();
}

void AssignmentList::editItem(QModelIndex model)
{
    QModelIndex sib = model.siblingAtColumn(3);

    int id = sib.data(0).toInt();
    DAOAssignment *dao = new DAOAssignmentSQLITE;
    Assignment assignment = dao->getAssignmentById(id);

    NewAssignmentWindow *newWindow = new NewAssignmentWindow(&assignment);
    newWindow->show();
    this->close();
}

void AssignmentList::onDeleteItem()
{
    QItemSelectionModel *select = _view.selectionModel();

    if(select->hasSelection())
    {
        QModelIndexList models = select->selectedRows();

        QModelIndex model = select->selectedRows().takeAt(0);
        QVariant description = model.data(0);
        QModelIndex sib = model.siblingAtColumn(3);
        QVariant id = sib.data(0).toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirme", "Apagar a tarefa '"+description.toString()+"'?",
                                     QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            DAOAssignment *dao = new DAOAssignmentSQLITE;
            Assignment assignment = dao->getAssignmentById(id.toInt());
            if(!dao->deleteAssignment(&assignment))
            {
                QMessageBox msg(QMessageBox::Critical, "Erro", "Erro ao apagar tarefa!");
                msg.exec();
                return;
            }
            _model.removeRow(model.row());
        }
    }
}
