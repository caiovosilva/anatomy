#ifndef DAOANSWER_H
#define DAOANSWER_H

#include "answer.h"

class DAOAnswer
{

public:
    virtual bool addAnswer(Answer *answer) = 0;
    virtual Answer getAnswer(int id) = 0;
    virtual Answer getAnswerByQuestion(int id) = 0;
    virtual bool deleteAnswer(Answer* answer) = 0;

signals:

public slots:
};

#endif // DAOANSWER_H
