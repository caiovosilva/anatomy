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

    QString description() const;
    void setDescription(const QString &value);

    QList<AnatomyImage> imageList() const;
    void setImageList(const QList<AnatomyImage> &value);

    int id() const;
    void setId(int id);

    int modalityId() const;
    void setModalityId(int value);

private:
    int _id;
    QList<AnatomyImage> _imageList;
    QString _description;
    int _modalityId;
};

#endif // ANATOMICALREGION_H
