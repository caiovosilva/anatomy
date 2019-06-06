#include "anatomicalregion.h"

AnatomicalRegion::AnatomicalRegion()
{
}

AnatomicalRegion::AnatomicalRegion(QString description):
    _description(description)
{
}

QString AnatomicalRegion::description() const
{
    return _description;
}

void AnatomicalRegion::setDescription(const QString &value)
{
    _description = value;
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
