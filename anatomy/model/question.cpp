#include "question.h"

Question::Question(QString description, int assignmentId):
    _description(description),
    _assignmentId(assignmentId)
{

}

Question::Question()
{
}

bool Question::operator==(const Question &question) const
{
    return (question.description() == description());
}

void Question::addAnswer(Answer answer)
{
    _answers.append(answer);
}

void Question::removeAnswer(Answer answer)
{
    _answers.removeOne(answer);
}

QString Question::description() const
{
    return _description;
}

int Question::id() const
{
    return _id;
}

void Question::setId(int id)
{
    _id = id;
}

int Question::correctAnswerId() const
{
    return _correctAnswerId;
}

void Question::setCorrectAnswerId(int correctAnswerId)
{
    _correctAnswerId = correctAnswerId;
}

int Question::assignmentId() const
{
    return _assignmentId;
}

void Question::setAssignmentId(int assignmentId)
{
    _assignmentId = assignmentId;
}

void Question::setDescription(const QString &description)
{
    _description = description;
}
