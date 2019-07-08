#include "daoanatomicalregionsqlite.h"
#include "daomodalitysqlite.h"

bool DAOAnatomicalRegionSQLITE::addOrUpdateAnatomicalRegion(AnatomicalRegion *anatomicalRegion)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();
    QSqlQuery query;

    if(anatomicalRegion->id() < 0) {
        query.prepare("INSERT INTO anatomicalregion (description, modality_fk) VALUES (:description, :modality_fk)");
        query.bindValue(":description", anatomicalRegion->description());
        query.bindValue(":modality_fk", anatomicalRegion->modalityId());
    }
    else {
        query.prepare("UPDATE anatomicalregion SET description=:description WHERE id==:id");
        query.bindValue(":id", QString::number(anatomicalRegion->id()));
        query.bindValue(":description", anatomicalRegion->description());
    }


    bool result = query.exec();
    _mydb->commit();
    return result;
}

QList<AnatomicalRegion> DAOAnatomicalRegionSQLITE::getAnatomicalRegionByModalityId(int modalityId)
{
    QSqlQuery query;
    QList<AnatomicalRegion> AnatomicalRegionList;
    if(!_mydb->isOpen()){
        return AnatomicalRegionList;
    }
    _mydb->transaction();

    query.prepare("SELECT * FROM anatomicalregion WHERE modality_fk = :modalityId");
    query.bindValue(":modalityId", modalityId);

    if(query.exec()){
        AnatomicalRegion item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setModalityId(query.value(2).toInt());
            AnatomicalRegionList.append(item);
        }
    }
    _mydb->commit();
    return AnatomicalRegionList;
}

AnatomicalRegion DAOAnatomicalRegionSQLITE::getAnatomicalRegionById(int id)
{
    QSqlQuery query;
    AnatomicalRegion item;
    if(!_mydb->open())
        return item;
    _mydb->transaction();

    query.prepare("SELECT * FROM anatomicalregion WHERE id = :id");
    query.bindValue(":id", id);
    if(query.exec())
        while(query.next()) {
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setModalityId(query.value(2).toInt());
        }

    _mydb->commit();
    return item;
}

AnatomicalRegion DAOAnatomicalRegionSQLITE::getAnatomicalRegionByDescription(QString description)
{
    QSqlQuery query;
    AnatomicalRegion item;
    if(!_mydb->open())
        return item;
    _mydb->transaction();

    query.prepare("SELECT * FROM anatomicalregion WHERE description = :description");
    query.bindValue(":description", description);
    if(query.exec())
        while(query.next()) {
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setModalityId(query.value(2).toInt());
        }

    _mydb->commit();
    return item;
}

QList<AnatomicalRegion> DAOAnatomicalRegionSQLITE::getAllAnatomicalRegion()
{
    QSqlQuery query;
    QList<AnatomicalRegion> AnatomicalRegionList;
    if(!_mydb->isOpen()){
        return AnatomicalRegionList;
    }
    _mydb->transaction();

    query.prepare("SELECT * FROM anatomicalregion");
    if(query.exec()){
        AnatomicalRegion item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setModalityId(query.value(2).toInt());
            AnatomicalRegionList.append(item);
        }
    }
    _mydb->commit();
    return AnatomicalRegionList;
}

bool DAOAnatomicalRegionSQLITE::deleteAnatomicalRegion(int id)
{
    QSqlQuery query;
    bool sucess = false;
    if(!_mydb->open())
        return sucess;
    _mydb->transaction();

    query.prepare("DELETE FROM anatomicalregion WHERE id = :id");
    query.bindValue(":id", id);
    if(query.exec())
        sucess = true;
    _mydb->commit();
    return sucess;
}
