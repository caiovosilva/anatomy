#ifndef ANATOMYIMAGE_H
#define ANATOMYIMAGE_H

#include <QString>
#include <QList>
#include "question.h"
class Question;

class AnatomyImage
{
public:
    AnatomyImage(QString imagePath, QString description);

    QString getImagePath() const;
    void addQuestion(Question *question);
    void removeQuestion(Question *question);
    QList<Question *> getQuestionsList() const;

    int getId() const;
    void setId(int id);

    QString getDescription() const;

private:
    int _id;
    QString _imagePath;
    QString _description;
    QList<Question *> _questionsList;
};

#endif // ANATOMYIMAGE_H
