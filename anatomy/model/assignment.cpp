#include "assignment.h"

Assignment::Assignment()
{

}

int Assignment::id() const
{
    return _id;
}

void Assignment::setId(int id)
{
    _id = id;
}

QString Assignment::description() const
{
    return _description;
}

void Assignment::setDescription(const QString &description)
{
    _description = description;
}

QList<AnatomyImage> Assignment::getAnatomyImageList() const
{
    return anatomyImageList;
}

void Assignment::setAnatomyImageList(const QList<AnatomyImage> &value)
{
    anatomyImageList = value;
}
