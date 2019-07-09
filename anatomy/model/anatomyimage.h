#ifndef ANATOMYIMAGE_H
#define ANATOMYIMAGE_H

#include <QString>
#include <QList>
#include "question.h"
#include <QPixmap>
class Question;

class AnatomyImage
{
public:
    AnatomyImage(QByteArray image, int assignmentId);
    AnatomyImage(QByteArray image);
    AnatomyImage();
    bool operator==(const AnatomyImage &image) const;

    int id() const;
    void setId(int id);

    int assignmentId() const;
    void setAssignmentId(int assignmentId);

    QByteArray image() const;
    void setImage(const QByteArray &image);

private:
    int _id;
    QByteArray _image;
    int _assignmentId;
};

#endif // ANATOMYIMAGE_H
