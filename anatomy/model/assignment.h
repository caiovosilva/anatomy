#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <QString>
#include <QList>

#include "model/question.h"
#include "anatomyimage.h"

class AnatomyImage;

class Assignment
{
public:
    Assignment();
    Assignment(QString description, int anatomicalRegionId);

    int id() const;
    void setId(int id);

    QString description() const;
    void setDescription(const QString &description);

    QList<AnatomyImage> anatomyImageList() const;
    void setAnatomyImageList(const QList<AnatomyImage> &value);
    void addnatomyImage(AnatomyImage item);
    void removenatomyImage(AnatomyImage item);

    int anatomicalRegionId() const;
    void setAnatomicalRegionId(int value);

    QList<Question> questionsList() const;
    void setQuestionsList(const QList<Question> &questionsList);
    void addQuestion(Question question);
    void removeQuestion(Question question);

private:
    int _id;
    QString _description;
    QList<AnatomyImage> _anatomyImageList;
    QList<Question> _questionsList;
    int _anatomicalRegionId;
};

#endif // ASSIGNMENT_H
