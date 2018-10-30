#include "question.h"

Question::Question(QString description, AnatomyImage *anatomyImage):
    _description(description),
    _anatomyImage(anatomyImage)
{

}

void Question::addAnswer(Answer *answer)
{
    _answers.append(answer);
}

void Question::removeAnswer(Answer *answer)
{
    _answers.removeOne(answer);
}

QString Question::description() const
{
    return _description;
}

int Question::id() const
{
    return _id;
}

void Question::setId(int id)
{
    _id = id;
}
