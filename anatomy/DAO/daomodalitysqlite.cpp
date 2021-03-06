#include "daomodalitysqlite.h"

bool DAOModalitySQLITE::addOrUpdateModality(Modality *modality)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    if(modality->id() < 0) {
        query.prepare("INSERT INTO modality (description) VALUES (:description)");
        query.bindValue(":description", modality->description());
    }
    else {
        query.prepare("UPDATE modality SET description=:description WHERE id==:id");
        query.bindValue(":id", QString::number(modality->id()));
        query.bindValue(":description", modality->description());
    }

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
        while(query.next()){
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
        while(query.next())
        {
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
        }

    _mydb->commit();
    return item;
}

Modality DAOModalitySQLITE::getModalityByDescription(QString description)
{
    QSqlQuery query;
    Modality item;
    if(!_mydb->open())
        return item;
    _mydb->transaction();

    query.prepare("SELECT * FROM modality WHERE description = :description");
    query.bindValue(":description", description);
    if(query.exec())
        while(query.next())
        {
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
        }

    _mydb->commit();
    return item;
}

bool DAOModalitySQLITE::deleteModality(int id)
{
    QSqlQuery query;
    bool sucess = false;
    if(!_mydb->open())
        return sucess;
    _mydb->transaction();

    query.prepare("DELETE FROM modality WHERE id = :id");
    query.bindValue(":id", id);
    if(query.exec())
        sucess = true;
    _mydb->commit();
    return sucess;
}
