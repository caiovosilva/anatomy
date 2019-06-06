#include "daoanatomicalregionsqlite.h"

bool DAOAnatomicalRegionSQLITE::addAnatomicalRegion(AnatomicalRegion *anatomicalRegion)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO anatomicalregion (description, modality_fk) VALUES (:description, :modality_fk)");
    query.bindValue(":description", anatomicalRegion->description());
    query.bindValue(":modality_fk", anatomicalRegion->modalityId());

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
