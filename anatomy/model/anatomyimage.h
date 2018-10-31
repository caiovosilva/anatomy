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
    AnatomyImage();

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

private:
    int _id;
    QString _imagePath;
    QString _description;
    QList<Question> _questionsList;
};

#endif // ANATOMYIMAGE_H
