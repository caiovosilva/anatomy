#ifndef DAOASSIGNMENT_H
#define DAOASSIGNMENT_H

#include "model/assignment.h"

class DAOAssignment
{
public:
    virtual bool addAssignment(Assignment *assignment) = 0;
//    virtual QList<Modality> getAllAssignments() = 0;
//    virtual Modality getAssignment(int id) = 0;
//    virtual bool deleteAssignment(Modality* modality) = 0;
};

#endif // DAOASSIGNMENT_H
