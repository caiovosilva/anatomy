#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

class DBConnection
{
public:
    static DBConnection* Instance();
    QSqlDatabase *Connection();

protected:
    DBConnection();

private:
    static DBConnection* _instance;
    QSqlDatabase mydb;
};

#endif // DBCONNECTION_H
