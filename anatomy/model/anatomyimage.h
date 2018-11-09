#ifndef ANATOMYIMAGE_H
#define ANATOMYIMAGE_H

#include <QString>
#include <QList>
#include "question.h"
class Question;

class AnatomyImage
{
public:
    AnatomyImage(QString imagePath, int assignmentId);
    AnatomyImage();
    bool operator==(const AnatomyImage &image) const;

    int getId() const;
    void setId(int id);

    void setImagePath(const QString &imagePath);
    QString getImagePath() const;

    int getAssignmentId() const;
    void setAssignmentId(int assignmentId);

private:
    int _id;
    QString _imagePath;
    int _assignmentId;
};

#endif // ANATOMYIMAGE_H
