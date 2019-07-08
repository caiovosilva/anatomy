#ifndef ASSIGNMENTMODEL_H
#define ASSIGNMENTMODEL_H

#include <QAbstractTableModel>
#include "assignment.h"

class AssignmentModel : public QAbstractTableModel
{
    QList<Assignment> m_data;
public:
    AssignmentModel(QObject * parent = {}) : QAbstractTableModel{parent} {}
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void append(const Assignment & assignment);
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
};

#endif // ASSIGNMENTMODEL_H
