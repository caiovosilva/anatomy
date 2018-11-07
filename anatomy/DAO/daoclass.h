#ifndef DAOCLASS_H
#define DAOCLASS_H

#include "dbconnection.h"

#include <QtSql>

class DAOClass
{
public:
    DAOClass();

protected:
    QSqlDatabase *_mydb;
};

#endif // DAOCLASS_H
