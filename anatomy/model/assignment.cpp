#include "assignment.h"

Assignment::Assignment():
    _id(-1)
{
}

Assignment::Assignment(QString description, int anatomicalRegionId):
    _id(-1),
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

QList<AnatomyImage> Assignment::anatomyImageList() const
{
    return _anatomyImageList;
}

void Assignment::setAnatomyImageList(const QList<AnatomyImage> &value)
{
    _anatomyImageList = value;
}

void Assignment::addnatomyImage(AnatomyImage item)
{
    _anatomyImageList.append(item);
}

void Assignment::removenatomyImage(AnatomyImage item)
{
    _anatomyImageList.removeOne(item);
}

int Assignment::anatomicalRegionId() const
{
    return _anatomicalRegionId;
}

void Assignment::setAnatomicalRegionId(int value)
{
    _anatomicalRegionId = value;
}

QList<Question> Assignment::questionsList() const
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

