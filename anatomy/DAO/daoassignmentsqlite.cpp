#include "daoassignmentsqlite.h"
#include "daoanatomyimagesqlite.h"
#include "daoquestionsqlite.h"

bool DAOAssignmentSQLITE::addOrUpdateAssignment(Assignment *assignment)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    if(assignment->id() < 0) {
        query.prepare("INSERT INTO assignment (description, anatomicalRegion_fk) VALUES (:description, :anatomicalRegion_fk)");
        query.bindValue(":description", assignment->description());
        query.bindValue(":anatomicalRegion_fk", assignment->anatomicalRegionId());
    }
    else {
        query.prepare("UPDATE assignment SET description=:description, anatomicalRegion_fk=:anatomicalRegion_fk WHERE id==:id");
        query.bindValue(":id", QString::number(assignment->id()));
        query.bindValue(":description", assignment->description());
        query.bindValue(":anatomicalRegion_fk", assignment->anatomicalRegionId());
    }

    bool result = query.exec();
    if(assignment->id() < 0)
    {
        assignment->setId(query.lastInsertId().toInt());

    }
    if(result)
    {
        DAOAnatomyImage *daoAnatomyImage = new DAOAnatomyImageSQLITE;
        foreach (AnatomyImage item, assignment->anatomyImageList())
        {
            if(item.id() < 1)
            {
                item.setAssignmentId(assignment->id());
                result &= daoAnatomyImage->addAnatomyImage(&item);
            }
        }
    }
    if(result)
        _mydb->commit();
    return result;
}

QList<Assignment> DAOAssignmentSQLITE::getAllAssignments()
{
    QSqlQuery query;
    QList<Assignment> assignmentsList;
    if(!_mydb->open())
        return assignmentsList;
    _mydb->transaction();

    query.prepare("SELECT * FROM assignment");
    if(query.exec()){
        while(query.next()){
            Assignment item;
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setAnatomicalRegionId(query.value(2).toInt());
            assignmentsList.append(item);
        }
    }
    QList<Assignment> assignmentsDefinitiveList;
    foreach (Assignment item, assignmentsList) {
        DAOAnatomyImage *daoAnatomyImage = new DAOAnatomyImageSQLITE;
        item.setAnatomyImageList(daoAnatomyImage->getAllAnatomyImagesByAssignmentId(item.id()));
        DAOQuestion *daoQuestion = new DAOQuestionSQLITE;
        item.setQuestionsList(daoQuestion->getQuestionsByAssignmentId(item.id()));
        assignmentsDefinitiveList.append(item);
    }
    _mydb->commit();
    return assignmentsDefinitiveList;
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

Assignment* DAOAssignmentSQLITE::getAssignmentByDescription(QString description)
{
    QSqlQuery query;
    Assignment item;
    Assignment *assignment = nullptr;
    if(!_mydb->open())
        return assignment;
    _mydb->transaction();

    query.prepare("SELECT * FROM assignment WHERE description = :description");
    query.bindValue(":description", description);
    if(query.exec()){
        while(query.next())
        {
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setAnatomicalRegionId(query.value(2).toInt());
            DAOAnatomyImage *daoAnatomyImage = new DAOAnatomyImageSQLITE;
            item.setAnatomyImageList(daoAnatomyImage->getAllAnatomyImagesByAssignmentId(item.id()));
            DAOQuestion *daoQuestion = new DAOQuestionSQLITE;
            item.setQuestionsList(daoQuestion->getQuestionsByAssignmentId(item.id()));
            assignment = &item;
        }
    }

    _mydb->commit();
    return assignment;
}

bool DAOAssignmentSQLITE::deleteAssignment(Assignment *assignment)
{
    QSqlQuery query;
    bool sucess = true;
    if(!_mydb->open())
        return false;
    _mydb->transaction();

    DAOQuestion *daoQuestion = new DAOQuestionSQLITE;
    foreach (Question item, assignment->questionsList()) {
        sucess &= daoQuestion->deleteQuestion(&item);
    }
    DAOAnatomyImage *daoImage = new DAOAnatomyImageSQLITE;
    foreach (AnatomyImage item, assignment->anatomyImageList()) {
        sucess &= daoImage->deleteAnatomyImagesByAssignmentId(assignment->id());
    }

    if(sucess){
        query.prepare("DELETE FROM assignment WHERE id = :id");
        query.bindValue(":id", assignment->id());
        sucess &= query.exec();
    }
    if(sucess)
        _mydb->commit();
    return sucess;
}
