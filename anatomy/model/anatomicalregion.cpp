#include "anatomicalregion.h"

AnatomicalRegion::AnatomicalRegion()
{

}

void AnatomicalRegion::addImage(AnatomyImage image)
{
    imageList.append(image);
}

void AnatomicalRegion::removeImage(AnatomyImage image)
{
    imageList.removeOne(image);
}

QString AnatomicalRegion::getDescription() const
{
    return description;
}

void AnatomicalRegion::setDescription(const QString &value)
{
    description = value;
}

QList<AnatomyImage> AnatomicalRegion::getImageList() const
{
    return imageList;
}

void AnatomicalRegion::setImageList(const QList<AnatomyImage> &value)
{
    imageList = value;
}

int AnatomicalRegion::getId() const
{
    return _id;
}

void AnatomicalRegion::setId(int id)
{
    _id = id;
}

int AnatomicalRegion::getModalityId() const
{
    return modalityId;
}

void AnatomicalRegion::setModalityId(int value)
{
    modalityId = value;
}
