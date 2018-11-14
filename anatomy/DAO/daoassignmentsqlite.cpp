#include "daoassignmentsqlite.h"
#include "daoanatomyimagesqlite.h"
#include "daoquestionsqlite.h"

bool DAOAssignmentSQLITE::addAssignment(Assignment *assignment)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO assignment (description, anatomicalRegion_fk) VALUES (:description, :anatomicalRegion_fk)");
    query.bindValue(":description", assignment->description());
    query.bindValue(":anatomicalRegion_fk", assignment->anatomicalRegionId());

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

Assignment DAOAssignmentSQLITE::getAssignmentById(int id)
{
    QSqlQuery query;
    Assignment item;
    if(!_mydb->open())
        return item;
    _mydb->transaction();

    query.prepare("SELECT * FROM assignment WHERE id = :id");
    query.bindValue(":id", id);
    if(query.exec()){
        while(query.next())
        {
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setAnatomicalRegionId(query.value(2).toInt());
        }
    }
    DAOAnatomyImage *daoAnatomyImage = new DAOAnatomyImageSQLITE;
    item.setAnatomyImageList(daoAnatomyImage->getAllAnatomyImagesByAssignmentId(item.id()));
    DAOQuestion *daoQuestion = new DAOQuestionSQLITE;
    item.setQuestionsList(daoQuestion->getQuestionsByAssignmentId(item.id()));

    _mydb->commit();
    return item;
}
