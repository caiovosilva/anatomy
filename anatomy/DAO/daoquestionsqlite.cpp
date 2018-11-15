#include "daoquestionsqlite.h"
#include "daoanswersqlite.h"

bool DAOQuestionSQLITE::addQuestion(Question *question)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO question (description, assignment_fk) "
                  "VALUES (:description, :assignment_fk)");
    query.bindValue(":description", question->description());
    query.bindValue(":assignment_fk", question->assignmentId());

    bool result = query.exec();
    question->setId(query.lastInsertId().toInt());
    _mydb->commit();
    return result;
}

//Question DAOQuestionSQLITE::getQuestion(int id)
//{

//}

//bool DAOQuestionSQLITE::deleteQuestion(Question *question)
//{

//}

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
