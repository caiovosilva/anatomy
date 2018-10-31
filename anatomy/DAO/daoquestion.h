#ifndef DAOQUESTION_H
#define DAOQUESTION_H

#include "model/question.h"

class DAOQuestion
{
public:
    virtual bool addQuestion(Question *question) = 0;
    virtual Question getQuestion(int id) = 0;
    virtual QList<Question> getQuestionsByAnatomyImageId(int id) = 0;
    virtual bool deleteQuestion(Question* question) = 0;

private:
    virtual bool isOkToPersist(Question *question) = 0;
};

#endif // DAOQUESTION_H
