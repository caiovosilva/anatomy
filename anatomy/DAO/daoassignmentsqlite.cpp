#include "daoassignmentsqlite.h"

bool DAOAssignmentSQLITE::addAssignment(Assignment *assignment)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO modality (description) VALUES (:description)");
    //query.bindValue(":description", assignment->get());

    bool result = query.exec();
    _mydb->commit();
    return result;
}
