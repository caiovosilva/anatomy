#include "daoquestionsqlite.h"
#include "daoanswersqlite.h"

bool DAOQuestionSQLITE::addOrUpdateQuestion(Question *question)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    if(question->id() < 0)
    {
        query.prepare("INSERT INTO question (description, assignment_fk, anatomyImage_fk) "
                      "VALUES (:description, :assignment_fk, :anatomyImage_fk)");
        query.bindValue(":description", question->description());
        query.bindValue(":assignment_fk", question->assignmentId());
        query.bindValue(":anatomyImage_fk", question->anatomyImageId());
    }
    else
    {
        query.prepare("UPDATE question SET description=:description, assignment_fk=:assignment_fk, anatomyImage_fk=:anatomyImage_fk WHERE id==:id");
        query.bindValue(":id", QString::number(question->id()));
        query.bindValue(":description", question->description());
        query.bindValue(":assignment_fk", question->assignmentId());
        query.bindValue(":anatomyImage_fk", question->anatomyImageId());
    }

    bool result = query.exec();
    if(question->id() < 0)
        question->setId(query.lastInsertId().toInt());
    if(result)
    {
        DAOAnswer *dao = new DAOAnswerSQLITE;
        foreach (Answer item, question->answers())
        {
            item.setQuestionId(question->id());
            result &= dao->addOrUpdateAnswer(&item);
        }
    }
    if(result)
        _mydb->commit();
    return result;
}

QList<Question> DAOQuestionSQLITE::getQuestionsByAssignmentId(int id)
{
    QSqlQuery query;
    QList<Question> questionsList;
    if(!_mydb->isOpen())
        return questionsList;
    _mydb->transaction();

    query.prepare("SELECT * FROM question WHERE assignment_fk = :id");
    query.bindValue(":id", id);

    if(query.exec())
    {
        Question item;
        while(query.next())
        {
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setAssignmentId(query.value(2).toInt());
            questionsList.append(item);
        }
    }
    DAOAnswer *daoAnswer = new DAOAnswerSQLITE;
    for (int var = 0; var < questionsList.size(); var++)
    {
        questionsList[var].setAnswers(daoAnswer->getAnswersByQuestionId(questionsList[var].id()));
    }
    _mydb->commit();
    return questionsList;
}

QList<Question> DAOQuestionSQLITE::getQuestionsByAnatomyImageId(int id)
{
    QSqlQuery query;
    QList<Question> questionsList;
    if(!_mydb->isOpen())
        return questionsList;
    _mydb->transaction();

    query.prepare("SELECT * FROM question WHERE anatomyImage_fk = :id");
    query.bindValue(":id", id);

    if(query.exec())
    {
        Question item;
        while(query.next())
        {
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setAssignmentId(query.value(2).toInt());
            item.setAnatomyImageId(query.value(3).toInt());
            questionsList.append(item);
        }
    }
    DAOAnswer *daoAnswer = new DAOAnswerSQLITE;
    for (int var = 0; var < questionsList.size(); var++)
    {
        questionsList[var].setAnswers(daoAnswer->getAnswersByQuestionId(questionsList[var].id()));
    }
    _mydb->commit();
    return questionsList;
}

bool DAOQuestionSQLITE::updateQuestion(Question *question)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("UPDATE question SET description = :description, assignment_fk = :assignment_fk, "
                  "WHERE id = :id");
    query.bindValue(":description", question->description());
    query.bindValue(":assignment_fk", question->assignmentId());
    query.bindValue(":id", question->id());

    bool result = query.exec();
    _mydb->commit();
    return result;
}

bool DAOQuestionSQLITE::deleteQuestion(Question *question)
{
    QSqlQuery query;
    bool sucess = true;
    if(!_mydb->open())
        return false;
    _mydb->transaction();
    DAOAnswer *daoAnswer = new DAOAnswerSQLITE;
    foreach (Answer item, question->answers()) {
        sucess = sucess && daoAnswer->deleteAnswer(item.id());
    }
    if(sucess){
        query.prepare("DELETE FROM question WHERE id = :id");
        query.bindValue(":id", question->id());
        sucess = sucess && query.exec();
    }
    _mydb->commit();
    return sucess;
}

Question DAOQuestionSQLITE::getQuestionById(int id)
{
    QSqlQuery query;
    Question question;
    if(!_mydb->isOpen())
        return question;
    _mydb->transaction();

    query.prepare("SELECT * FROM question WHERE id = :id");
    query.bindValue(":id", id);

    if(query.exec())
    {
        while(query.next())
        {
            question.setId(query.value(0).toInt());
            question.setDescription(query.value(1).toString());
            question.setAssignmentId(query.value(2).toInt());
        }
    }
    DAOAnswer *daoAnswer = new DAOAnswerSQLITE;
    QList<Answer> ans = daoAnswer->getAnswersByQuestionId(question.id());
    question.setAnswers(ans);
    _mydb->commit();
    return question;
}
