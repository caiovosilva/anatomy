#ifndef ANSWER_H
#define ANSWER_H

#include <QString>

class Answer
{
public:
    Answer(QString description, bool isCorrectAnswer);
private:
    bool isCorrectAnswer;
    QString description;
};

#endif // ANSWER_H
