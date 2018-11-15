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

int Question::assignmentId() const
{
    return _assignmentId;
}

void Question::setAssignmentId(int assignmentId)
{
    _assignmentId = assignmentId;
}

QList<Answer> Question::answers() const
{
    return _answers;
}

void Question::setAnswers(const QList<Answer> &answers)
{
    _answers = answers;
}

void Question::setDescription(const QString &description)
{
    _description = description;
}
