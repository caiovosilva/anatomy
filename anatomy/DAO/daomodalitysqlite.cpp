#include "daomodalitysqlite.h"

bool DAOModalitySQLITE::addModality(Modality *modality)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO modality (description) VALUES (:description)");
    query.bindValue(":description", modality->description());

    bool result = query.exec();
    _mydb->commit();
    return result;
}

QList<Modality> DAOModalitySQLITE::getAllModalities()
{
    QSqlQuery query;
    QList<Modality> modalitiesList;
    if(!_mydb->open())
        return modalitiesList;
    _mydb->transaction();

    query.prepare("select * from modality");
    if(query.exec()){
        Modality item;
        while(query.next()) {
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            modalitiesList.append(item);
        }
    }
    _mydb->commit();
    return modalitiesList;
}

Modality DAOModalitySQLITE::getModalityById(int id)
{
    QSqlQuery query;
    Modality item;
    if(!_mydb->open())
        return item;
    _mydb->transaction();

    query.prepare("SELECT * FROM modality WHERE id = :id");
    query.bindValue(":id", id);
    if(query.exec())
        while(query.next()) {
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
        }

    _mydb->commit();
    return item;
}
