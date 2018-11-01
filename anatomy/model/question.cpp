#include "question.h"

Question::Question(QString description, int anatomyImageId):
    _description(description),
    _anatomyimageId(anatomyImageId)
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

int Question::anatomyimageId() const
{
    return _anatomyimageId;
}

void Question::setAnatomyimageId(int anatomyimageId)
{
    _anatomyimageId = anatomyimageId;
}

int Question::correctAnswerId() const
{
    return _correctAnswerId;
}

void Question::setCorrectAnswerId(int correctAnswerId)
{
    _correctAnswerId = correctAnswerId;
}

void Question::setDescription(const QString &description)
{
    _description = description;
}
