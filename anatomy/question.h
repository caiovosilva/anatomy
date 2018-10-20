#ifndef QUESTION_H
#define QUESTION_H

#include <QList>

#include "answer.h"

class Question
{
public:
    Question(QString description);
    void addAnswer(Answer *answer);
    void removeAnswer(Answer *answer);
    QString description() const;

private:
    QString _description;                            //oq fazer? um "get" e um "set" ou colocar como publico??
    QList<Answer*> answers;

};

#endif // QUESTION_H
