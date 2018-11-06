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

QList<Modality> DAOModalitySQLITE::getAllModalities()
{
    QSqlQuery query;
    QList<Modality> modalitiesList;
    _mydb->open();
    if(!_mydb->open())
        return modalitiesList;

    query.prepare("select * from modality");
    if(query.exec()){
        Modality item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            modalitiesList.append(item);
        }
    }
    _mydb->commit();
    _mydb->close();
    return modalitiesList;
}
