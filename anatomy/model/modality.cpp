#include "modality.h"

Modality::Modality(QString description):
    _id(-1), _description(description)
{
}

Modality::Modality(QString description, int id):
    _id(id), _description(description)
{
}

Modality::Modality():
    _id(-1)
{
}

Modality::~Modality()
{

}

int Modality::id() const
{
    return _id;
}

void Modality::setId(int value)
{
    _id = value;
}

QString Modality::description() const
{
    return _description;
}

void Modality::setDescription(const QString &value)
{
    _description = value;
}
