#ifndef DAOANSWER_H
#define DAOANSWER_H

#include "model/answer.h"

class DAOAnswer
{

public:
    virtual bool addOrUpdateAnswer(Answer *answer) = 0;
    virtual QList<Answer> getAnswersByQuestionId(int id) = 0;
    virtual bool deleteAnswer(int id) = 0;
    virtual ~DAOAnswer(){ }
};

#endif // DAOANSWER_H
