#ifndef QUESTIONMODEL_H
#define QUESTIONMODEL_H


#include <QAbstractTableModel>
#include "question.h"

class QuestionModel : public QAbstractTableModel
{
    QList<Question> m_data;
public:
    QuestionModel(QObject * parent = {}) : QAbstractTableModel{parent} {}
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void append(const Question & question);
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
};

#endif // QUESTIONMODEL_H
