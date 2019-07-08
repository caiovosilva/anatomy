#ifndef MODALITYMODEL_H
#define MODALITYMODEL_H

#include <QAbstractTableModel>
#include "modality.h"

class ModalityModel : public QAbstractTableModel
{
    QList<Modality> m_data;
public:
    ModalityModel(QObject * parent = {}) : QAbstractTableModel{parent} {}
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void append(const Modality & modality);
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
};

#endif // MODALITYMODEL_H
