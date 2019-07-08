#ifndef DAOANATOMICALREGIONSQLITE_H
#define DAOANATOMICALREGIONSQLITE_H

#include <QtSql>

#include "dbconnection.h"
#include "model/anatomicalregion.h"
#include "daoanatomicalregion.h"
#include "DAO/daoclass.h"

class DAOAnatomicalRegionSQLITE : public DAOAnatomicalRegion, public DAOClass
{
    // DAOAnatomicalRegion interface
public:
    bool addOrUpdateAnatomicalRegion(AnatomicalRegion *anatomicalRegion);
    QList<AnatomicalRegion> getAnatomicalRegionByModalityId(int modalityId);
    AnatomicalRegion getAnatomicalRegionById(int id);
    AnatomicalRegion getAnatomicalRegionByDescription(QString description);
    QList<AnatomicalRegion> getAllAnatomicalRegion();
    bool deleteAnatomicalRegion(int id);
};

#endif // DAOANATOMICALREGIONSQLITE_H
