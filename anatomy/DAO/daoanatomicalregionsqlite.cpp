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
    query.prepare("INSERT INTO anatomicalregion (description, modalityId) VALUES (:description, :modality_fk)");
    query.bindValue(":description", anatomicalRegion->getDescription());
    query.bindValue(":modality_fk", anatomicalRegion->getModalityId());

    bool result = query.exec();
    _mydb->commit();
    _mydb->close();
    return result;
}
