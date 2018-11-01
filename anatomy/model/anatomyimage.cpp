#include "anatomyimage.h"

AnatomyImage::AnatomyImage(QString imagePath, QString description):
    _imagePath(imagePath),
    _description(description)
{

}

AnatomyImage::AnatomyImage()
{
}

bool AnatomyImage::operator==(const AnatomyImage &image) const
{
    return image.getDescription() == getDescription();
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

QString AnatomyImage::getDescription() const
{
    return _description;
}

void AnatomyImage::setDescription(const QString &description)
{
    _description = description;
}

void AnatomyImage::setImagePath(const QString &imagePath)
{
    _imagePath = imagePath;
}

