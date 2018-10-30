#include "answer.h"

Answer::Answer(QString description, bool isCorrectAnswer) :
    _description(description),
    _isCorrectAnswer(isCorrectAnswer)
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

int Answer::id() const
{
    return _id;
}

void Answer::setId(int id)
{
    _id = id;
}
