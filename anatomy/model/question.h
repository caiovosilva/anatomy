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
    Question(QString description, int assignmentId);
    Question();

    bool operator==(const Question &question) const;

    void addAnswer(Answer answer);
    void removeAnswer(Answer answer);

    int id() const;
    void setId(int id);

    QString description() const;
    void setDescription(const QString &description);

    int assignmentId() const;
    void setAssignmentId(int assignmentId);

    QList<Answer> answers() const;
    void setAnswers(const QList<Answer> &answers);

    int anatomyImageId() const;
    void setAnatomyImageId(int anatomyImageId);

private:
    int _id;
    QString _description;
    QList<Answer> _answers;
    int _assignmentId;
    int _anatomyImageId;
};

#endif // QUESTION_H
