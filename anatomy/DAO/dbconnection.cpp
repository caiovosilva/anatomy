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
    CreateTables();
}

void DBConnection::CreateTables()
{
    QSqlQuery qry;

    qry.prepare( "CREATE TABLE IF NOT EXISTS `modality` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `description` TEXT NOT NULL )" );
    if( !qry.exec() )
        qDebug() << qry.lastError();

    qry.prepare( "CREATE TABLE `anatomicalregion` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `description` TEXT NOT NULL, `modality_fk` INTEGER NOT NULL,FOREIGN KEY(`modality_fk`) REFERENCES `modality`(`id`))" );
    if( !qry.exec() )
        qDebug() << qry.lastError();

    qry.prepare( "CREATE TABLE IF NOT EXISTS `assignment` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `description` TEXT NOT NULL, `anatomicalRegion_fk` INTEGER NOT NULL, FOREIGN KEY(`anatomicalRegion_fk`) REFERENCES `anatomicalregion`(`id`) )" );
    if( !qry.exec() )
        qDebug() << qry.lastError();

    qry.prepare( "CREATE TABLE `anatomyimage` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `image` BLOB NOT NULL, `assignment_fk` INTEGER NOT NULL, FOREIGN KEY(`assignment_fk`) REFERENCES `assignment`(`id`) )" );
    if( !qry.exec() )
        qDebug() << qry.lastError();

    qry.prepare( "CREATE TABLE IF NOT EXISTS `question` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `description`	TEXT NOT NULL, `assignment_fk` INTEGER NOT NULL, FOREIGN KEY(`assignment_fk`) REFERENCES `assignment`(`id`) )" );
    if( !qry.exec() )
        qDebug() << qry.lastError();

    qry.prepare( "CREATE TABLE IF NOT EXISTS `answer` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `description` TEXT NOT NULL, `isCorrectAnswer`	INTEGER NOT NULL, `question_fk`	INTEGER NOT NULL, FOREIGN KEY(`question_fk`) REFERENCES `question`(`id`) )" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
}


