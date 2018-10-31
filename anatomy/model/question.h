#ifndef QUESTION_H
#define QUESTION_H

#include <QList>

#include "answer.h"
#include "anatomyimage.h"

class AnatomyImage;
class Answer;

class Question
{
public:
    Question(QString description, int anatomyImageId);
    Question();

    bool operator==(const Question &question) const;

    void addAnswer(Answer answer);
    void removeAnswer(Answer answer);
    int id() const;
    void setId(int id);
    QString description() const;
    void setDescription(const QString &description);
    int anatomyimageId() const;
    void setAnatomyimageId(int anatomyimageId);

private:
    int _id;
    QString _description;
    QList<Answer> _answers;
    int _anatomyimageId;
};

#endif // QUESTION_H
