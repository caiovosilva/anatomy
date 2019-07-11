#ifndef DAOQUESTION_H
#define DAOQUESTION_H

#include "model/question.h"

class DAOQuestion
{
public:
    virtual bool addOrUpdateQuestion(Question *question) = 0;
    virtual QList<Question> getQuestionsByAssignmentId(int id) = 0;
    virtual Question getQuestionById(int id) = 0;
    virtual bool updateQuestion(Question *question) = 0;
    virtual bool deleteQuestion(Question *question) = 0;
    virtual ~DAOQuestion(){ }
};

#endif // DAOQUESTION_H
