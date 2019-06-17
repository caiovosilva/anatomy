#ifndef MODALITYMODEL_H
#define MODALITYMODEL_H

#include <QAbstractTableModel>
#include "modality.h"

class ModalityModel : public QAbstractTableModel
{
    QList<Modality> m_data;
public:
    ModalityModel(QObject * parent = {}) : QAbstractTableModel{parent} {}
    int rowCount(const QModelIndex &) const override { return m_data.count(); }
       int columnCount(const QModelIndex &) const override { return 1; }
       QVariant data(const QModelIndex &index, int role) const override {
          if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
          const auto & modality = m_data[index.row()];
          switch (index.column()) {
          case 0: return modality.description();
//          case 1: return vehicle.model();
//          case 2: return vehicle.registrationNumber();
          default: return {};
          };
       }
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
         if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
//         switch (section) {
//         case 0: return "Make";
//         case 1: return "Model";
//         case 2: return "Reg.#";
//         default: return {};
//         }
         return "Descrição";
      }
   void append(const Modality & modality) {
         beginInsertRows({}, m_data.count(), m_data.count());
         m_data.append(modality);
         endInsertRows();
      }
};

#endif // MODALITYMODEL_H
