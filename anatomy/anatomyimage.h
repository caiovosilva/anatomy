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

    QString getImagePath() const;
    void addQuestion(Question *question);
    void removeQuestion(Question *question);
    QList<Question *> getQuestionsList() const;

private:
    QString imagePath;
    QList<Question *> questionsList;
};

#endif // ANATOMYIMAGE_H
