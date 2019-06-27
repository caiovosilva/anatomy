#include "modalitymodel.h"

int ModalityModel::rowCount(const QModelIndex &) const
{
    return m_data.count();
}

int ModalityModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant ModalityModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
    const auto & modality = m_data[index.row()];
    switch (index.column()) {
    case 0: return modality.description();
//          case 1: return vehicle.model();
//          case 2: return vehicle.registrationNumber();
    default: return {};
    };
}

QVariant ModalityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
//         switch (section) {
//         case 0: return "Make";
//         case 1: return "Model";
//         case 2: return "Reg.#";
//         default: return {};
//         }
    return "Descrição";
}

void ModalityModel::append(const Modality &modality)
{
    beginInsertRows({}, m_data.count(), m_data.count());
    m_data.append(modality);
    endInsertRows();
}
