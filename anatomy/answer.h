#ifndef ANSWER_H
#define ANSWER_H

#include <QString>
//#include <QObject>

class Answer /*: public QObject*/
{
    //Q_OBJECT

public:
    Answer(QString description, bool isCorrectAnswer);
    QString description() const;
    bool operator==(const Answer &aws) const;

    int id() const;
    void setId(int id);

private:
    int _id;
    bool _isCorrectAnswer;
    QString _description;
};

#endif // ANSWER_H
