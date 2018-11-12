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

    int id() const;
    void setId(int id);

    void setImagePath(const QString &imagePath);
    QString imagePath() const;

    int assignmentId() const;
    void setAssignmentId(int assignmentId);

private:
    int _id;
    QString _imagePath;
    int _assignmentId;
};

#endif // ANATOMYIMAGE_H
