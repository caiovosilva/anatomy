#include "listquestionswindow.h"
#include "ui_listquestionswindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
#include <QIcon>

ListQuestionsWindow::ListQuestionsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListQuestionsWindow)
{
    ui->setupUi(this);
    m_pTableWidget = new QTableWidget(this);
    m_pTableWidget->setRowCount(10);
    m_pTableWidget->setColumnCount(3);
    m_TableHeader<<"Pergunta"<<"Editar";
    m_pTableWidget->setColumnWidth(0,500);
    m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    m_pTableWidget->verticalHeader()->setVisible(false);
    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableWidget->setShowGrid(false);
    m_pTableWidget->setStyleSheet("QTableView {selection-background-color: red;}");
    m_pTableWidget->setGeometry(QApplication::desktop()->screenGeometry());

    //insert data
    m_pTableWidget->setItem(0, 0, new QTableWidgetItem("Hello"));

    connect( m_pTableWidget, SIGNAL( cellDoubleClicked (int, int) ),
        this, SLOT( cellSelected( int, int ) ) );
}

ListQuestionsWindow::~ListQuestionsWindow()
{
    delete ui;
}

void ListQuestionsWindow::cellSelected(int nRow, int nCol)
{
     QMessageBox::information(this, "",
         "Cell at row "+QString::number(nRow)+
         " column "+QString::number(nCol)+
         " was double clicked.");
}
