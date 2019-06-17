#include "modalitylist.h"
#include "ui_modalitylist.h"


modalityList::modalityList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modalityList)
{
    ui->setupUi(this);

//    QScreen *screen = QGuiApplication::primaryScreen();
//    QRect rec = screen->
//     height = screen->height();
//     width = screen->width();

}

modalityList::~modalityList()
{
    delete ui;
}

void modalityList::Widget()
{
    m_layout.addWidget(&m_view, 0, 0, 1, 1);
    m_layout.addWidget(&m_button, 1, 0, 1, 1);
    connect(&m_button, SIGNAL(clicked()), &m_dialog, SLOT(open()));
    //m_model.append({"Volvo", "240", "SQL8941"});
    m_model.append({"Volvooo"});
    m_model.append({"Volvooooo"});
    m_model.append({"Volvooooo"});
    m_proxy.setSourceModel(&m_model);
    m_proxy.setFilterKeyColumn(2);
    m_view.setModel(&m_proxy);
    m_dialog.setLabelText("Enter registration number fragment to filter on. Leave empty to clear filter.");
    m_dialog.setInputMode(QInputDialog::TextInput);
    connect(&m_dialog, SIGNAL(textValueSelected(QString)),
            &m_proxy, SLOT(setFilterFixedString(QString)));
}
