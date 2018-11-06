#ifndef DAOMODALITYSQLITE_H
#define DAOMODALITYSQLITE_H

#include "daomodality.h"
#include "dbconnection.h"

#include <QtSql>

class DAOModalitySQLITE : public DAOModality
{
public:
    DAOModalitySQLITE();

private:
    QSqlDatabase *_mydb;

    // DAOModality interface
public:
    bool addModality(Modality *modality);
    QList<Modality> getAllModalities();
};

#endif // DAOMODALITYSQLITE_H
