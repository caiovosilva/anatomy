#ifndef DAOASSIGNMENTSQLITE_H
#define DAOASSIGNMENTSQLITE_H

#include <QSqlDatabase>

#include "dbconnection.h"
#include "daoassignment.h"
#include "DAO/daoclass.h"

class DAOAssignmentSQLITE : public DAOAssignment, public DAOClass
{
    // DAOAssignment interface
public:
    bool addOrUpdateAssignment(Assignment *assignment);
    QList<Assignment> getAllAssignments();
    QList<Assignment> getAssignmentsByAnatomicalRegion(int anatomicalRegionId);
    Assignment getAssignmentById(int id);
    Assignment* getAssignmentByDescription(QString description);
    bool deleteAssignment(Assignment *assignment);
};

#endif // DAOASSIGNMENTSQLITE_H
