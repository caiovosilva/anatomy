#include "answer.h"

Answer::Answer(QString description, bool isCorrectAnswer, int questionId) :
    _description(description),
    _isCorrectAnswer(isCorrectAnswer),
    _questionId(questionId)
{
}

Answer::Answer()
{
}

bool Answer::operator==(const Answer &aws) const
{
    return aws.getDescription() == getDescription();
}

int Answer::id() const
{
    return _id;
}

void Answer::setId(int id)
{
    _id = id;
}

int Answer::getQuestionId() const
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

QString Answer::getDescription() const
{
    return _description;
}

void Answer::setDescription(const QString &description)
{
    _description = description;
}
