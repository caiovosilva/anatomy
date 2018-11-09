#include "assignment.h"

Assignment::Assignment()
{

}

Assignment::Assignment(QString description, int anatomicalRegionId):
    _description(description),
    _anatomicalRegionId(anatomicalRegionId)
{
}

int Assignment::id() const
{
    return _id;
}

void Assignment::setId(int id)
{
    _id = id;
}

QString Assignment::description() const
{
    return _description;
}

void Assignment::setDescription(const QString &description)
{
    _description = description;
}

QList<AnatomyImage> Assignment::getAnatomyImageList() const
{
    return _anatomyImageList;
}

void Assignment::setAnatomyImageList(const QList<AnatomyImage> &value)
{
    _anatomyImageList = value;
}

int Assignment::getAnatomicalRegionId() const
{
    return _anatomicalRegionId;
}

void Assignment::setAnatomicalRegionId(int value)
{
    _anatomicalRegionId = value;
}

QList<Question> Assignment::getQuestionsList() const
{
    return _questionsList;
}

void Assignment::setQuestionsList(const QList<Question> &questionsList)
{
    _questionsList = questionsList;
}

void Assignment::addQuestion(Question question)
{
    _questionsList.append(question);
}

void Assignment::removeQuestion(Question question)
{
    _questionsList.removeOne(question);
}

