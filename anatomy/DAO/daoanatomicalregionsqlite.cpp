#include "daoanatomicalregionsqlite.h"

DAOAnatomicalRegionSQLITE::DAOAnatomicalRegionSQLITE()
{
    _mydb = DBConnection::Instance()->Connection();
}

bool DAOAnatomicalRegionSQLITE::addAnatomicalRegion(AnatomicalRegion *anatomicalRegion)
{
    _mydb->open();
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO anatomicalregion (description, modality_fk) VALUES (:description, :modality_fk)");
    query.bindValue(":description", anatomicalRegion->getDescription());
    query.bindValue(":modality_fk", anatomicalRegion->getModalityId());

    bool result = query.exec();
    _mydb->commit();
    _mydb->close();
    return result;
}

QList<AnatomicalRegion> DAOAnatomicalRegionSQLITE::getAnatomicalRegionByModalityId(int modalityId)
{
    QSqlQuery query;
    QList<AnatomicalRegion> AnatomicalRegionList;
    _mydb->open();
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
    _mydb->close();
    return AnatomicalRegionList;
}
