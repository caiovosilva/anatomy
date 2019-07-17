#include "questionlist.h"
#include "ui_questionlist.h"

#include "windows/newquestionwindow.h"
#include "model/question.h"
#include "model/answer.h"
#include "model/assignment.h"
#include "model/modality.h"
#include "DAO/daoassignmentsqlite.h"
#include "DAO/daoquestionsqlite.h"
#include "DAO/daoanswersqlite.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoanatomicalregionsqlite.h"

QuestionList::QuestionList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionList)
{
    ui->setupUi(this);
    _btnDeleteItem = ui->deleteQuestionButton;
    _btnAddItem = ui->addNewQuestionButton;
    _view = ui->tableView;
    setWindowTitle("Questões");

    QList<Modality> modalitiesList;
    DAOModality *daoModality = new DAOModalitySQLITE;
    modalitiesList = daoModality->getAllModalities();

    foreach (Modality item, modalitiesList) {
        ui->modalitiesComboBox->addItem(item.description(), item.id());
    }

    QPalette pal = _btnDeleteItem->palette();
    pal.setColor(QPalette::Button, QColor(Qt::red));
    _btnDeleteItem->setAutoFillBackground(true);
    _btnDeleteItem->setPalette(pal);
    _btnDeleteItem->update();
    QPalette pal2 = _btnAddItem->palette();
    pal2.setColor(QPalette::Button, QColor(Qt::green));
    _btnAddItem->setAutoFillBackground(true);
    _btnAddItem->setPalette(pal2);
    _btnAddItem->update();

    on_searchButton_clicked();
    _proxy.setSourceModel(&_model);
    _view->setModel(&_model);
    _view->resizeColumnsToContents();
    _view->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(_view, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(editItem(QModelIndex)));
    delete daoModality;
}

QuestionList::~QuestionList()
{
    delete ui;
}

void QuestionList::on_modalitiesComboBox_currentIndexChanged(int index)
{
    int modalityId = ui->modalitiesComboBox->currentData().toInt();

    QList<AnatomicalRegion> anatomicalRegionList;
    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE;
    anatomicalRegionList = daoAnatomicalRegion->getAnatomicalRegionByModalityId(modalityId);

    ui->anatomicalRegionComboBox->clear();
    foreach (AnatomicalRegion item, anatomicalRegionList) {
        ui->anatomicalRegionComboBox->addItem(item.description(), item.id());
    }

    delete daoAnatomicalRegion;
}

void QuestionList::on_anatomicalRegionComboBox_currentIndexChanged(int index)
{
    int anatomicalRegionId = ui->anatomicalRegionComboBox->currentData().toInt();

    QList<Assignment> assignmentList;
    DAOAssignment *assignmentDAO = new DAOAssignmentSQLITE;
    DAOQuestion *questionsDAO = new DAOQuestionSQLITE;
    assignmentList = assignmentDAO->getAssignmentsByAnatomicalRegion(anatomicalRegionId);

    ui->assignmentComboBox->clear();
    foreach (Assignment item, assignmentList) {
        item.setQuestionsList(questionsDAO->getQuestionsByAssignmentId(item.id()));
        ui->assignmentComboBox->addItem(item.description(), item.id());
    }
}

void QuestionList::on_addNewQuestionButton_clicked()
{
    NewQuestionWindow *newWindow = new NewQuestionWindow;
    newWindow->show();
    close();
}

void QuestionList::on_searchButton_clicked()
{
    int assignmentId = ui->assignmentComboBox->currentData().toInt();
    QList<Question> questionList;
    DAOQuestion *dao = new DAOQuestionSQLITE;
    questionList = dao->getQuestionsByAssignmentId(assignmentId);

    _model.resetData();
    foreach (Question item, questionList) {
        _model.append(item);
    }

    delete dao;
}

void QuestionList::editItem(QModelIndex model)
{
    QVariant description = model.data(0);
    QModelIndex sib = model.siblingAtColumn(1);
    QVariant id = sib.data(0).toInt();
    DAOQuestion *dao = new DAOQuestionSQLITE;
    Question question = dao->getQuestionById(id.toInt());
    NewQuestionWindow *newWindow = new NewQuestionWindow(&question);
    newWindow->show();
    this->close();
}

void QuestionList::on_deleteQuestionButton_clicked()
{
    QItemSelectionModel *select = _view->selectionModel();

    if(select->hasSelection())
    {
        QModelIndexList models = select->selectedRows();

        QModelIndex model = select->selectedRows().takeAt(0);
        //select->selectedColumns(); // return selected column(s)
        QVariant description = model.data(0);
        QModelIndex sib = model.siblingAtColumn(1);
        QVariant id = sib.data(0).toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirme", "Apagar a questão '"+description.toString()+"'?",
                                     QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            DAOQuestion *dao = new DAOQuestionSQLITE;
            Question question = dao->getQuestionById(id.toInt());
            if(!dao->deleteQuestion(&question))
            {
                QMessageBox msg(QMessageBox::Critical, "Erro", "Erro ao apagar questão!");
                msg.exec();
                return;
            }
            _model.removeRow(model.row());
        }
    }
}
