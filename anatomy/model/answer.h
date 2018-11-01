#ifndef ANSWER_H
#define ANSWER_H

#include <QString>

#include "question.h"

class Question;

class Answer
{

public:
    Answer(QString description, bool isCorrectAnswer, int questionId);
    Answer();
    bool operator==(const Answer &aws) const;

    int id() const;
    void setId(int id);
    int getQuestionId() const;
    void setQuestionId(int value);
    bool isCorrectAnswer() const;
    void setIsCorrectAnswer(bool isCorrectAnswer);
    QString getDescription() const;
    void setDescription(const QString &description);

private:
    int _id;
    int _questionId;
    bool _isCorrectAnswer;
    QString _description;
};

#endif // ANSWER_H
