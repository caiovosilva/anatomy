#ifndef DAOANSWERSQLITE_H
#define DAOANSWERSQLITE_H

#include <QtSql>

#include "dbconnection.h"
#include "daoanswer.h"

class DAOAnswerSQLITE : public DAOAnswer
{

public:
    explicit DAOAnswerSQLITE(QObject *parent = nullptr);

    // DAOAnswer interface
public:
    bool addAnswer(Answer *answer);
    Answer getAnswer(int id);
    Answer getAnswerByQuestion(int id);
    bool deleteAnswer(Answer *answer);

private:
    QSqlDatabase *_mydb;
};

#endif // DAOANSWERSQLITE_H
