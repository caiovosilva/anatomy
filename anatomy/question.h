#ifndef QUESTION_H
#define QUESTION_H

#include <QList>

#include "answer.h"
#include "anatomyimage.h"
class AnatomyImage;
class Question
{
public:
    Question(QString description, AnatomyImage *anatomyImage);
    void addAnswer(Answer *answer);
    void removeAnswer(Answer *answer);
    QString description() const;

private:
    QString _description;                            //oq fazer? um "get" e um "set" ou colocar como publico??
    QList<Answer*> _answers;
    AnatomyImage *_anatomyImage;
};

#endif // QUESTION_H
