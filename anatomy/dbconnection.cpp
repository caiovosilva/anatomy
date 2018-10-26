#include "dbconnection.h"

DBConnection* DBConnection::_instance = NULL;

DBConnection *DBConnection::Instance()
{
    if(!_instance)
        _instance = new DBConnection;
    return _instance;
}

QSqlDatabase *DBConnection::Connection()
{
    return &mydb;
}

DBConnection::DBConnection()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(qApp->applicationDirPath()+"/anatomy");
}
