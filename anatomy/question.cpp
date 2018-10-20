#include "question.h"

Question::Question(QString description):
    _description(description)
{

}

void Question::addAnswer(Answer *answer)
{
    answers.append(answer);
}

void Question::removeAnswer(Answer *answer)
{
    answers.removeOne(answer);
}

QString Question::description() const
{
    return _description;
}
