#ifndef ANSWER_H
#define ANSWER_H

#include <QString>
//#include <QObject>

class Answer /*: public QObject*/
{
    //Q_OBJECT

public:
    Answer(QString _description, bool isCorrectAnswer);
    QString description() const;
    bool operator==(const Answer &aws) const;

private:
    bool isCorrectAnswer;
    QString _description;
};

#endif // ANSWER_H
