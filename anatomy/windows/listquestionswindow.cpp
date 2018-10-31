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
    _pTableWidget = new QTableWidget(this);
    _pTableWidget->setRowCount(10);
    _pTableWidget->setColumnCount(3);
    _TableHeader<<"Pergunta"<<"Editar";
    _pTableWidget->setColumnWidth(0,500);
    _pTableWidget->setHorizontalHeaderLabels(_TableHeader);
    _pTableWidget->verticalHeader()->setVisible(false);
    _pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    _pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    _pTableWidget->setShowGrid(false);
    _pTableWidget->setStyleSheet("QTableView {selection-background-color: red;}");
    _pTableWidget->setGeometry(QApplication::desktop()->screenGeometry());

    //insert data
    _pTableWidget->setItem(0, 0, new QTableWidgetItem("Hello"));

    connect( _pTableWidget, SIGNAL( cellDoubleClicked (int, int) ),
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
