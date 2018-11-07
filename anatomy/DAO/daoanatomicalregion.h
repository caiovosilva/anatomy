#ifndef DAOANATOMICALREGION_H
#define DAOANATOMICALREGION_H

#include "model/anatomicalregion.h"
class DAOAnatomicalRegion
{
public:
    virtual bool addAnatomicalRegion(AnatomicalRegion *anatomicalRegion) = 0;
    virtual QList<AnatomicalRegion> getAnatomicalRegionByModalityId(int modalityId) = 0;
};

#endif // DAOANATOMICALREGION_H