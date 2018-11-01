#include "daomodalitysqlite.h"

DAOModalitySQLITE::DAOModalitySQLITE()
{
    _mydb = DBConnection::Instance()->Connection();

}

bool DAOModalitySQLITE::addModality(Modality *modality)
{
    _mydb->open();
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO modality (description) VALUES (:description)");
    query.bindValue(":description", modality->getDescription());

    bool result = query.exec();
    _mydb->commit();
    _mydb->close();
    return result;
}
