#include "daoanswersqlite.h"

bool DAOAnswerSQLITE::addAnswer(Answer *answer)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO answer (description, isCorrectAnswer, question_fk) "
                  "VALUES (:description, :isCorrectAnswer, :question_fk)");
    query.bindValue(":description", answer->getDescription());
    query.bindValue(":isCorrectAnswer", answer->isCorrectAnswer());
    query.bindValue(":question_fk", answer->questionId());

    bool result = query.exec();
    answer->setId(query.lastInsertId().toInt());
    _mydb->commit();
    return result;
}

//Answer DAOAnswerSQLITE::getAnswer(int id)
//{

//}

//Answer DAOAnswerSQLITE::getAnswerByQuestion(int id)
//{

//}

//bool DAOAnswerSQLITE::deleteAnswer(Answer *answer)
//{

//}
