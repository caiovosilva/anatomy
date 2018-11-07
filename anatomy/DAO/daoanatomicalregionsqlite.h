#ifndef DAOANATOMICALREGIONSQLITE_H
#define DAOANATOMICALREGIONSQLITE_H

#include <QtSql>

#include "dbconnection.h"
#include "model/anatomicalregion.h"
#include "daoanatomicalregion.h"

class DAOAnatomicalRegionSQLITE : public DAOAnatomicalRegion
{
public:
    DAOAnatomicalRegionSQLITE();

private:
    QSqlDatabase *_mydb;

    // DAOAnatomicalRegion interface
public:
    bool addAnatomicalRegion(AnatomicalRegion *anatomicalRegion);
    QList<AnatomicalRegion> getAnatomicalRegionByModalityId(int modalityId);
};

#endif // DAOANATOMICALREGIONSQLITE_H
