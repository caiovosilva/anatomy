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
    return image.imagePath() == imagePath();
}

QString AnatomyImage::imagePath() const
{
    return _imagePath;
}

int AnatomyImage::assignmentId() const
{
    return _assignmentId;
}

void AnatomyImage::setAssignmentId(int assignmentId)
{
    _assignmentId = assignmentId;
}

int AnatomyImage::id() const
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

