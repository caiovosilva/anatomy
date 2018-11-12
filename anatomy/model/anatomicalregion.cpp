#include "anatomicalregion.h"

AnatomicalRegion::AnatomicalRegion()
{

}

void AnatomicalRegion::addImage(AnatomyImage image)
{
    _imageList.append(image);
}

void AnatomicalRegion::removeImage(AnatomyImage image)
{
    _imageList.removeOne(image);
}

QString AnatomicalRegion::description() const
{
    return _description;
}

void AnatomicalRegion::setDescription(const QString &value)
{
    _description = value;
}

QList<AnatomyImage> AnatomicalRegion::imageList() const
{
    return _imageList;
}

void AnatomicalRegion::setImageList(const QList<AnatomyImage> &value)
{
    _imageList = value;
}

int AnatomicalRegion::id() const
{
    return _id;
}

void AnatomicalRegion::setId(int id)
{
    _id = id;
}

int AnatomicalRegion::modalityId() const
{
    return _modalityId;
}

void AnatomicalRegion::setModalityId(int value)
{
    _modalityId = value;
}
