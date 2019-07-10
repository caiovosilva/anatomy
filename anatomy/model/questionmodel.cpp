#include "questionmodel.h"
#include "DAO/daoassignmentsqlite.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoanatomicalregionsqlite.h"

int QuestionModel::rowCount(const QModelIndex &) const
{
    return m_data.count();
}

int QuestionModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant QuestionModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
    const auto & question = m_data[index.row()];
    switch (index.column()) {
    case 0: return question.description();
    case 1: return question.id();
    default: return {};
    };
}

QVariant QuestionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
         switch (section) {
         case 0: return "Descrição";
         case 1: return "Identificador";
         default: return {};
         }
}

void QuestionModel::append(const Question &question)
{
    beginInsertRows({}, m_data.count(), m_data.count());
    m_data.append(question);
    endInsertRows();
}

bool QuestionModel::removeRows(int position, int rows, const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

        for (int row = 0; row < rows; ++row) {
            m_data.removeAt(position);
        }

    endRemoveRows();
    return true;
}

void QuestionModel::resetData()
{
    m_data.clear();
}
