#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <QString>
#include <QList>

#include "anatomyimage.h"
class AnatomyImage;

class Assignment
{
public:
    Assignment();
    Assignment(QString description, int anatomicalRegionId);

    int id() const;
    void setId(int id);

    QString description() const;
    void setDescription(const QString &description);

    QList<AnatomyImage> getAnatomyImageList() const;
    void setAnatomyImageList(const QList<AnatomyImage> &value);

    int getAnatomicalRegionId() const;
    void setAnatomicalRegionId(int value);

private:
    int _id;
    QString _description;
    QList<AnatomyImage> _anatomyImageList;
    int _anatomicalRegionId;
};

#endif // ASSIGNMENT_H
