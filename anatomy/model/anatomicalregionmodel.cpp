#include "anatomicalregionmodel.h"

int AnatomicalRegionModel::rowCount(const QModelIndex &) const
{
    return m_data.count();
}

int AnatomicalRegionModel::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant AnatomicalRegionModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
    const auto & modality = m_data[index.row()];
    switch (index.column()) {
    case 0: return modality.description();
    case 1: return modality.id();
    //default: return {};
    };
}

QVariant AnatomicalRegionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
         switch (section) {
         case 0: return "Descrição";
         case 1: return "Id";
         default: return {};
         }
}

void AnatomicalRegionModel::append(const AnatomicalRegion &anatomicalRegion)
{
    beginInsertRows({}, m_data.count(), m_data.count());
    m_data.append(anatomicalRegion);
    endInsertRows();
}

void AnatomicalRegionModel::clearData()
{
    m_data.clear();
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
