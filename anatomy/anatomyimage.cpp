#include "anatomyimage.h"

AnatomyImage::AnatomyImage(QString imagePath):
    imagePath(imagePath)
{

}

QString AnatomyImage::getImagePath() const
{
    return imagePath;
}

void AnatomyImage::addQuestion(Question *question)
{
    questionsList.append(question);
}

void AnatomyImage::removeQuestion(Question *question)
{
    questionsList.removeOne(question);
}

QList<Question *> AnatomyImage::getQuestionsList() const
{
    return questionsList;
}

