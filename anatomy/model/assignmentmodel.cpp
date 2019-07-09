#include "assignmentmodel.h"
#include "DAO/daoassignmentsqlite.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoanatomicalregionsqlite.h"

int AssignmentModel::rowCount(const QModelIndex &) const
{
    return m_data.count();
}

int AssignmentModel::columnCount(const QModelIndex &) const
{
    return 4;
}

QVariant AssignmentModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
    const auto & assignment = m_data[index.row()];
    DAOAnatomicalRegion *daoAnatomicalRegion = new DAOAnatomicalRegionSQLITE;
    AnatomicalRegion anatomicalRegion = daoAnatomicalRegion->getAnatomicalRegionById(assignment.anatomicalRegionId());
    DAOModality *daoModality = new DAOModalitySQLITE;
    QString modalityDescription = daoModality->getModalityById(anatomicalRegion.modalityId()).description();
    switch (index.column()) {
    case 0: return assignment.description();
    case 1: return modalityDescription;
    case 2: return anatomicalRegion.description();
    case 3: return assignment.id();
    default: return {};
    };
}

QVariant AssignmentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
         switch (section) {
         case 0: return "Descrição";
         case 1: return "Modalidade";
         case 2: return "Região Anatômica";
         case 3: return "Identificador";
         default: return {};
         }
}

void AssignmentModel::append(const Assignment &assignment)
{
    beginInsertRows({}, m_data.count(), m_data.count());
    m_data.append(assignment);
    endInsertRows();
}

bool AssignmentModel::removeRows(int position, int rows, const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

        for (int row = 0; row < rows; ++row) {
            m_data.removeAt(position);
        }

    endRemoveRows();
    return true;
}
