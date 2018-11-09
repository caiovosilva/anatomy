#include "anatomyimage.h"

AnatomyImage::AnatomyImage(QString imagePath, int assignmentId):
    _imagePath(imagePath),
    _assignmentId(assignmentId)
{

}

AnatomyImage::AnatomyImage()
{
}

bool AnatomyImage::operator==(const AnatomyImage &image) const
{
    return image.getImagePath() == getImagePath();
}

QString AnatomyImage::getImagePath() const
{
    return _imagePath;
}

QList<Question> AnatomyImage::getQuestionsList() const
{
    return _questionsList;
}

void AnatomyImage::setQuestionsList(const QList<Question> &questionsList)
{
    _questionsList = questionsList;
}

int AnatomyImage::getAssignmentId() const
{
    return _assignmentId;
}

void AnatomyImage::setAssignmentId(int assignmentId)
{
    _assignmentId = assignmentId;
}

void AnatomyImage::addQuestion(Question question)
{
    _questionsList.append(question);
}

void AnatomyImage::removeQuestion(Question question)
{
    _questionsList.removeOne(question);
}

int AnatomyImage::getId() const
{
    return _id;
}

void AnatomyImage::setId(int id)
{
    _id = id;
}

void AnatomyImage::setImagePath(const QString &imagePath)
{
    _imagePath = imagePath;
}

