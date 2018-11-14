#ifndef DAOANSWERSQLITE_H
#define DAOANSWERSQLITE_H

#include <QtSql>

#include "dbconnection.h"
#include "daoanswer.h"
#include "DAO/daoclass.h"

class DAOAnswerSQLITE : public DAOAnswer, public DAOClass
{
    // DAOAnswer interface
public:
    bool addAnswer(Answer *answer);
    QList<Answer> getAnswersByQuestionId(int id);
//    Answer getAnswer(int id);
//    bool deleteAnswer(Answer *answer);

};

#endif // DAOANSWERSQLITE_H
