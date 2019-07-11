#ifndef DAOANATOMICALREGION_H
#define DAOANATOMICALREGION_H

#include "model/anatomicalregion.h"
class DAOAnatomicalRegion
{
public:
    virtual bool addOrUpdateAnatomicalRegion(AnatomicalRegion *anatomicalRegion) = 0;
    virtual QList<AnatomicalRegion> getAnatomicalRegionByModalityId(int modalityId) = 0;
    virtual AnatomicalRegion getAnatomicalRegionById(int id) = 0;
    virtual AnatomicalRegion getAnatomicalRegionByDescription(QString description) = 0;
    virtual QList<AnatomicalRegion> getAllAnatomicalRegion() = 0;
    virtual bool deleteAnatomicalRegion(int id) = 0;
    virtual ~DAOAnatomicalRegion(){ }
};

#endif // DAOANATOMICALREGION_H

