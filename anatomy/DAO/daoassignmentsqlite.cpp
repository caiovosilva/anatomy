#include "daoassignmentsqlite.h"

bool DAOAssignmentSQLITE::addAssignment(Assignment *assignment)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO assignment (description, anatomicalRegion_fk) VALUES (:description, :anatomicalRegion_fk)");
    query.bindValue(":description", assignment->description());
    query.bindValue(":anatomicalRegion_fk", assignment->getAnatomicalRegionId());

    bool result = query.exec();
    assignment->setId(query.lastInsertId().toInt());
    _mydb->commit();
    return result;
}
