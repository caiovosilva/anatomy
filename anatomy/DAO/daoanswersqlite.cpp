#include "daoanswersqlite.h"

bool DAOAnswerSQLITE::addOrUpdateAnswer(Answer *answer)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    if(answer->id() < 0) {
        query.prepare("INSERT INTO answer (description, isCorrectAnswer, question_fk) "
                      "VALUES (:description, :isCorrectAnswer, :question_fk)");
        query.bindValue(":description", answer->description());
        query.bindValue(":isCorrectAnswer", answer->isCorrectAnswer());
        query.bindValue(":question_fk", answer->questionId());
    }
    else {
        query.prepare("UPDATE answer SET description=:description, isCorrectAnswer=:isCorrectAnswer, question_fk=:question_fk WHERE id==:id");
        query.bindValue(":description", answer->description());
        query.bindValue(":isCorrectAnswer", answer->isCorrectAnswer());
        query.bindValue(":question_fk", answer->questionId());
        query.bindValue(":id", answer->id());
    }

    bool result = query.exec();
    answer->setId(query.lastInsertId().toInt());
    _mydb->commit();
    return result;
}

QList<Answer> DAOAnswerSQLITE::getAnswersByQuestionId(int id)
{
    QSqlQuery query;
    QList<Answer> answerList;
    if(!_mydb->open())
        return answerList;
    _mydb->transaction();

    query.prepare("SELECT * FROM answer WHERE question_fk = :question_fk");
    query.bindValue(":question_fk", id);

    if(query.exec()){
        Answer item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setIsCorrectAnswer(query.value(2).toInt());
            item.setQuestionId(query.value(3).toInt());
            answerList.append(item);
        }
    }
    _mydb->commit();
    return answerList;
}

bool DAOAnswerSQLITE::deleteAnswer(int id)
{
    QSqlQuery query;
    bool sucess = false;
    if(!_mydb->open())
        return sucess;
    _mydb->transaction();

    query.prepare("DELETE FROM answer WHERE id = :id");
    query.bindValue(":id", id);
    if(query.exec())
        sucess = true;
    _mydb->commit();
    return sucess;
}
