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
