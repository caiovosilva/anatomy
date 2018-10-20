#include "answer.h"

Answer::Answer(QString description, bool isCorrectAnswer) :
    _description(description),
    isCorrectAnswer(isCorrectAnswer)
{
}

QString Answer::description() const
{
    return _description;
}

bool Answer::operator==(const Answer &aws) const
{
    return aws.description() == description();
}
