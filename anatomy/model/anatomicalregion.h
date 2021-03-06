#ifndef ANATOMICALREGION_H
#define ANATOMICALREGION_H

#include "anatomyimage.h"
#include "modality.h"
#include "QString"

class AnatomicalRegion
{
public:
    AnatomicalRegion();
    AnatomicalRegion(QString description);
    AnatomicalRegion(QString description, int id);

    QString description() const;
    void setDescription(const QString &value);

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
