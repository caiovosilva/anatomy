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

QList<Assignment> DAOAssignmentSQLITE::getAllAssignments()
{
    QSqlQuery query;
    QList<Assignment> assignmentsList;
    //DAOQuestion *questionsDAO = new DAOQuestionSQLITE;
    if(!_mydb->open())
        return assignmentsList;
    _mydb->transaction();

    query.prepare("SELECT * FROM assignment");
    if(query.exec()){
        Assignment item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setAnatomicalRegionId(query.value(2).toInt());
            //item.setQuestionsList(questionsDAO->getQuestionsByAssignmentId(item.id()));
            assignmentsList.append(item);
        }
    }
    _mydb->commit();
    return assignmentsList;
}

QList<Assignment> DAOAssignmentSQLITE::getAssignmentsByAnatomicalRegion(int anatomicalRegionId)
{
    QSqlQuery query;
    QList<Assignment> assignmentsList;
    if(!_mydb->open())
        return assignmentsList;
    _mydb->transaction();

    query.prepare("SELECT * FROM assignment WHERE anatomicalRegion_fk = :anatomicalRegion_fk");
    query.bindValue(":anatomicalRegion_fk", anatomicalRegionId);
    if(query.exec()){
        Assignment item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setAnatomicalRegionId(query.value(2).toInt());
            assignmentsList.append(item);
        }
    }
    _mydb->commit();
    return assignmentsList;
}
