#include "modalitylist.h"
#include "ui_modalitylist.h"

#include "DAO/daomodalitysqlite.h"
#include "windows/newmodalitywindow.h"

ModalityList::ModalityList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModalityList)
{
    ui->setupUi(this);

    QPalette pal = _btnDeleteModality.palette();
    pal.setColor(QPalette::Button, QColor(Qt::red));
    _btnDeleteModality.setAutoFillBackground(true);
    _btnDeleteModality.setPalette(pal);
    _btnDeleteModality.update();
    QPalette pal2 = _btnAddModality.palette();
    pal2.setColor(QPalette::Button, QColor(Qt::green));
    _btnAddModality.setAutoFillBackground(true);
    _btnAddModality.setPalette(pal2);
    _btnAddModality.update();

    _layout.addWidget(&_view, 0, 0, 1, 1);
    _layout.addWidget(&_btnAddModality, 1, 0, 1, 1);
    _layout.addWidget(&_btnDeleteModality, 2, 0, 1, 1);
    connect(&_btnAddModality, SIGNAL(clicked()), this, SLOT(newModalityButtonClicked()));
    connect(&_btnDeleteModality, SIGNAL(clicked()), this, SLOT(onDeleteModality()));
    fillTable();
    _proxy.setSourceModel(&_model);
    _view.setModel(&_proxy);
    _view.resizeColumnsToContents();
    _view.setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(&_view, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(editModality(QModelIndex)));

//    m_proxy.setFilterKeyColumn(2);
//    m_dialog.setLabelText("Tem certeza que deseja apagar este item?");
//    m_dialog.setInputMode(QInputDialog::TextInput);
//    connect(&m_dialog, SIGNAL(textValueSelected(QString)),
//            &m_proxy, SLOT(setFilterFixedString(QString)));
}

ModalityList::~ModalityList()
{
    delete ui;
}

void ModalityList::fillTable()
{
    _model.clearData();
    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        _model.append(item);
    }

    delete daoModality;
}

void ModalityList::newModalityButtonClicked()
{
    NewModalityWindow *newWindow = new NewModalityWindow;
    newWindow->show();
}

void ModalityList::editModality(QModelIndex model)
{
    QVariant description = model.data(0);
    QModelIndex sib = model.siblingAtColumn(1);
    QVariant id = sib.data(0).toInt();
    Modality modality(description.toString(), id.toInt());

    NewModalityWindow *newWindow = new NewModalityWindow(&modality);
    newWindow->show();
}

void ModalityList::onDeleteModality()
{
    QItemSelectionModel *select = _view.selectionModel();

    if(select->hasSelection())
    {
        QModelIndexList models = select->selectedRows();

        QModelIndex model = select->selectedRows().takeAt(0);
        //select->selectedColumns(); // return selected column(s)
        QVariant description = model.data(0);
        QModelIndex sib = model.siblingAtColumn(1);
        QVariant id = sib.data(0).toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirme", "Tem certeza que deseja apagar a modalidade "+description.toString()+"?",
                                     QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            DAOModality *daoModality = new DAOModalitySQLITE;
            bool result = daoModality->deleteModality(id.toInt());
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
