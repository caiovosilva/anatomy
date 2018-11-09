#ifndef DAOQUESTIONSQLITE_H
#define DAOQUESTIONSQLITE_H

#include "model/question.h"
#include "daoquestion.h"
#include "dbconnection.h"
#include "DAO/daoclass.h"

#include <QtSql>

class DAOQuestionSQLITE : public DAOQuestion, public DAOClass
{
    // DAOQuestion interface
public:
    bool addQuestion(Question *question);
//    Question getQuestion(int id);
//    bool deleteQuestion(Question *question);
    QList<Question> getQuestionsByAssignmentId(int id);
    bool updateQuestion(Question *question);

};

#endif // DAOQUESTIONSQLITE_H
