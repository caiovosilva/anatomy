#ifndef ANATOMICALREGIONMODEL_H
#define ANATOMICALREGIONMODEL_H

#include <QAbstractTableModel>
#include "anatomicalregion.h"

class AnatomicalRegionModel : public QAbstractTableModel
{
    QList<AnatomicalRegion> m_data;
public:
    AnatomicalRegionModel(QObject * parent = {}) : QAbstractTableModel{parent} {}
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void append(const AnatomicalRegion & anatomicalRegion);
    void clearData();
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
};

#endif // ANATOMICALREGIONMONDEL_H
