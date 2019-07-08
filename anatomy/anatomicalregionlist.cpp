#include "anatomicalregionlist.h"
#include "ui_anatomicalregionlist.h"

#include "DAO/daoanatomicalregionsqlite.h"
#include "windows/newanatomicalregionwindow.h"

AnatomicalRegionList::AnatomicalRegionList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnatomicalRegionList)
{
    ui->setupUi(this);

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

AnatomicalRegionList::~AnatomicalRegionList()
{
    delete ui;
}

void AnatomicalRegionList::fillTable()
{
    _model.clearData();
    QList<AnatomicalRegion> anatomicalRegionList;
    DAOAnatomicalRegion *daoModality = new DAOAnatomicalRegionSQLITE;
    anatomicalRegionList = daoModality->getAllAnatomicalRegion();

    foreach (AnatomicalRegion item, anatomicalRegionList) {
        _model.append(item);
    }

    delete daoModality;
}

void AnatomicalRegionList::newItem()
{
    NewAnatomicalRegionWindow *newWindow = new NewAnatomicalRegionWindow;
    newWindow->show();
    this->close();
}

void AnatomicalRegionList::editItem(QModelIndex model)
{
//    QString description = model.data(0).toString();
//    QModelIndex sib = model.siblingAtColumn(1);

//    DAOModality *daoModality = new DAOModalitySQLITE;
//    Modality modality = daoModality->getModalityByDescription(sib.data(0).toString());
    QModelIndex sib = model.siblingAtColumn(2);

    int id = sib.data(0).toInt();
    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE;
    AnatomicalRegion anatomicalRegion = daoAnatomicalRegion->getAnatomicalRegionById(id);

    NewAnatomicalRegionWindow *newWindow = new NewAnatomicalRegionWindow(&anatomicalRegion);
    newWindow->show();
    this->close();
}

void AnatomicalRegionList::onDeleteItem()
{
    QItemSelectionModel *select = _view.selectionModel();

    if(select->hasSelection())
    {
        QModelIndexList models = select->selectedRows();

        QModelIndex model = select->selectedRows().takeAt(0);
        //select->selectedColumns(); // return selected column(s)
        QVariant description = model.data(0);
        QModelIndex sib = model.siblingAtColumn(2);
        QVariant id = sib.data(0).toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirme", "Tem certeza que deseja apagar a região anatômica '"+description.toString()+"'?",
                                     QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE;
            bool result = daoAnatomicalRegion->deleteAnatomicalRegion(id.toInt());
            if(!result)
            {
                QMessageBox msg(QMessageBox::Critical, "Erro", "Erro ao apagar modalidade!");
                msg.exec();
                return;
            }
            _model.removeRow(model.row());
        }
    }
}
