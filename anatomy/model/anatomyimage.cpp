#include "anatomyimage.h"

AnatomyImage::AnatomyImage(QByteArray image, int assignmentId):
    _id(-1),
    _image(image),
    _assignmentId(assignmentId)
{

}

AnatomyImage::AnatomyImage(QByteArray image):
    _id(-1),
    _image(image)
{
}

AnatomyImage::AnatomyImage():
    _id(-1)
{
}

bool AnatomyImage::operator==(const AnatomyImage &image) const
{
    return image.id() == id();
}



int AnatomyImage::assignmentId() const
{
    return _assignmentId;
}

void AnatomyImage::setAssignmentId(int assignmentId)
{
    _assignmentId = assignmentId;
}

QByteArray AnatomyImage::image() const
{
    return _image;
}

void AnatomyImage::setImage(const QByteArray &image)
{
    _image = image;
}

int AnatomyImage::id() const
{
    return _id;
}

void AnatomyImage::setId(int id)
{
    _id = id;
}
