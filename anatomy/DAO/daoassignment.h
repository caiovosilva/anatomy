#ifndef DAOASSIGNMENT_H
#define DAOASSIGNMENT_H

#include "model/assignment.h"

class DAOAssignment
{
public:
    virtual bool addAssignment(Assignment *assignment) = 0;
    virtual QList<Assignment> getAllAssignments() = 0;
    virtual QList<Assignment> getAssignmentsByAnatomicalRegion(int anatomicalRegionId) = 0;
    virtual Assignment getAssignmentById(int id) = 0;
    virtual Assignment* getAssignmentByDescription(QString description) = 0;
//    virtual bool deleteAssignment(Modality* modality) = 0;
};

#endif // DAOASSIGNMENT_H
