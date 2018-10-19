#ifndef QUESTION_H
#define QUESTION_H

#include <QList>

#include "answer.h";

class Question
{
public:
    Question();
    void addAnswer(Answer *answer);
    void removeAnswer(Answer *answer);
    QString description;                            //oq fazer? um "get" e um "set" ou colocar como publico??

private:
    QList<Answer> answers;

};

#endif // QUESTION_H
