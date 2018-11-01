#ifndef ANATOMICALREGION_H
#define ANATOMICALREGION_H

#include "anatomyimage.h"
#include "QString"

class AnatomicalRegion
{
public:
    AnatomicalRegion();
    void addImage(AnatomyImage image);
    void removeImage(AnatomyImage image);
    QString getDescription() const;
    void setDescription(const QString &value);
    QList<AnatomyImage> getImageList() const;
    void setImageList(const QList<AnatomyImage> &value);

private:
    QList<AnatomyImage> imageList;
    QString description;
};

#endif // ANATOMICALREGION_H
