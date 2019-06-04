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
    return &_mydb;
}

DBConnection::DBConnection()
{
    _mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString appDir = qApp->applicationDirPath();
    if(!QDir(appDir+ "/database").exists())
        QDir().mkdir(appDir+ "/database");
    _mydb.setDatabaseName(qApp->applicationDirPath()+"/database/anatomy.db");
    _mydb.open();
}
