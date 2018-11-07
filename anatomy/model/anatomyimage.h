#ifndef ANATOMYIMAGE_H
#define ANATOMYIMAGE_H

#include <QString>
#include <QList>
#include "question.h"
class Question;

class AnatomyImage
{
public:
    AnatomyImage(QString imagePath);
    AnatomyImage();
    bool operator==(const AnatomyImage &image) const;

    void addQuestion(Question question);
    void removeQuestion(Question question);

    int getId() const;
    void setId(int id);

    QString getDescription() const;
    void setDescription(const QString &description);

    void setImagePath(const QString &imagePath);
    QString getImagePath() const;

    QList<Question> getQuestionsList() const;
    void setQuestionsList(const QList<Question> &questionsList);

    int getAssignmentId() const;
    void setAssignmentId(int assignmentId);

private:
    int _id;
    QString _imagePath;
    QList<Question> _questionsList;
    int _assignmentId;
};

#endif // ANATOMYIMAGE_H
