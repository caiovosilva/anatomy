#ifndef DAOMODALITYSQLITE_H
#define DAOMODALITYSQLITE_H

#include "daomodality.h"
#include "dbconnection.h"
#include "DAO/daoclass.h"

#include <QtSql>

class DAOModalitySQLITE : public DAOModality, public DAOClass
{
    // DAOModality interface
public:
    bool addOrUpdateModality(Modality *modality);
    QList<Modality> getAllModalities();
    Modality getModalityById(int id);
    Modality getModalityByDescription(QString description);
    bool deleteModality(int id);
};

#endif // DAOMODALITYSQLITE_H
