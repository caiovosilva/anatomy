#include "modality.h"

Modality::Modality(QString description):
    _description(description)
{
}

Modality::Modality()
{
}

int Modality::getId() const
{
    return _id;
}

void Modality::setId(int value)
{
    _id = value;
}

QString Modality::getDescription() const
{
    return _description;
}

void Modality::setDescription(const QString &value)
{
    _description = value;
}
