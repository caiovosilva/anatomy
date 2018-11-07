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

    int id() const;
    void setId(int id);

    QString description() const;
    void setDescription(const QString &description);

    QList<AnatomyImage> getAnatomyImageList() const;
    void setAnatomyImageList(const QList<AnatomyImage> &value);

private:
    int _id;
    QString _description;
    QList<AnatomyImage> anatomyImageList;
};

#endif // ASSIGNMENT_H
