#ifndef DAOQUESTIONSQLITE_H
#define DAOQUESTIONSQLITE_H

#include "model/question.h"
#include "daoquestion.h"
#include "dbconnection.h"

#include <QtSql>

class DAOQuestionSQLITE : public DAOQuestion
{
public:
    DAOQuestionSQLITE();

    // DAOQuestion interface
public:
    bool addQuestion(Question *question);
    Question getQuestion(int id);
    bool deleteQuestion(Question *question);
    QList<Question> getQuestionsByAnatomyImageId(int id);


private:
    QSqlDatabase *_mydb;

};

#endif // DAOQUESTIONSQLITE_H
