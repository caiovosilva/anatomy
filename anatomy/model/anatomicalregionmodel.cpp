#include "anatomicalregionmodel.h"
#include "DAO/daomodalitysqlite.h"

int AnatomicalRegionModel::rowCount(const QModelIndex &) const
{
    return m_data.count();
}

int AnatomicalRegionModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant AnatomicalRegionModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
    const auto & anatomicalRegion = m_data[index.row()];
    DAOModality *daoModality = new DAOModalitySQLITE;
    QString modalityDescription = daoModality->getModalityById(anatomicalRegion.modalityId()).description();
    switch (index.column()) {
    case 0: return anatomicalRegion.description();
    case 1: return modalityDescription;
    case 2: return anatomicalRegion.id();
    default: return {};
    };
}

QVariant AnatomicalRegionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
         switch (section) {
         case 0: return "Descrição";
         case 1: return "Modalidade";
         case 2: return "Identificador";
         default: return {};
         }
}

void AnatomicalRegionModel::append(const AnatomicalRegion &anatomicalRegion)
{
    beginInsertRows({}, m_data.count(), m_data.count());
    m_data.append(anatomicalRegion);
    endInsertRows();
}

bool AnatomicalRegionModel::removeRows(int position, int rows, const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

        for (int row = 0; row < rows; ++row) {
            m_data.removeAt(position);
        }

    endRemoveRows();
    return true;
}
