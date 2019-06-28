#include "modalitylist.h"
#include "ui_modalitylist.h"

#include "DAO/daomodalitysqlite.h"
#include "windows/newmodalitywindow.h"

ModalityList::ModalityList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModalityList)
{
    ui->setupUi(this);

    m_layout.addWidget(&m_view, 0, 0, 1, 1);
    m_layout.addWidget(&m_button, 1, 0, 1, 1);
    connect(&m_button, SIGNAL(clicked()), this, SLOT(newModalityButtonClicked()));
    fillTable();
    m_proxy.setSourceModel(&m_model);
    m_view.setModel(&m_proxy);
    m_view.resizeColumnsToContents();
    connect(&m_view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(editModality(QModelIndex)));
    //m_proxy.setFilterKeyColumn(2);
//    m_dialog.setLabelText("Enter registration number fragment to filter on. Leave empty to clear filter.");
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
    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        m_model.append({item.description(), item.id()});
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
