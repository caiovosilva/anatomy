#include "answer.h"

Answer::Answer(QString description, bool isCorrectAnswer, int questionId) :
    _id(-1),
    _questionId(questionId),
    _isCorrectAnswer(isCorrectAnswer),
    _description(description)
{
}

Answer::Answer():
    _id(-1)
{
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

int Answer::questionId() const
{
    return _questionId;
}

void Answer::setQuestionId(int value)
{
    _questionId = value;
}

bool Answer::isCorrectAnswer() const
{
    return _isCorrectAnswer;
}

void Answer::setIsCorrectAnswer(bool isCorrectAnswer)
{
    _isCorrectAnswer = isCorrectAnswer;
}

QString Answer::description() const
{
    return _description;
}

void Answer::setDescription(const QString &description)
{
    _description = description;
}
