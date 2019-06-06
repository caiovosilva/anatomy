#ifndef DAOMODALITY_H
#define DAOMODALITY_H

#include "model/modality.h"

class DAOModality
{
public:
    virtual bool addModality(Modality *modality) = 0;
    virtual QList<Modality> getAllModalities() = 0;
    virtual Modality getModalityById(int id) = 0;
//    virtual bool deleteModality(Modality* modality) = 0;
};

#endif // DAOMODALITY_H
