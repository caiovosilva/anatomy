#ifndef DAOMODALITY_H
#define DAOMODALITY_H

#include "model/modality.h"

class DAOModality
{
public:
    virtual bool addOrUpdateModality(Modality *modality) = 0;
    virtual QList<Modality> getAllModalities() = 0;
    virtual Modality getModalityById(int id) = 0;
    virtual Modality getModalityByDescription(QString description) = 0;
    virtual bool deleteModality(int id) = 0;
    virtual ~DAOModality(){ }
};

#endif // DAOMODALITY_H
