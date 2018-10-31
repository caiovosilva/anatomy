#include "daoquestionsqlite.h"

DAOQuestionSQLITE::DAOQuestionSQLITE()
{
    _mydb = DBConnection::Instance()->Connection();
}

bool DAOQuestionSQLITE::addQuestion(Question *question)
{
    _mydb->open();
    if(!isOkToPersist(question) || !_mydb->isOpen())
    {
        _mydb->close();
        return false;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO question (description, anatomyimage_fk) "
                  "VALUES (:description, :anatomyimage_fk)");
    query.bindValue(":description", question->description());
    query.bindValue(":anatomyimage_fk", question->anatomyimageId());
    return query.exec();
//    return(query.exec("INSERT INTO question(description, anatomyimage_fk) VALUES ('"
//               +question->description()+ ", "+ question->anatomyimageId()+")"));
}

Question DAOQuestionSQLITE::getQuestion(int id)
{

}

bool DAOQuestionSQLITE::deleteQuestion(Question *question)
{

}

QList<Question> DAOQuestionSQLITE::getQuestionsByAnatomyImageId(int id)
{
    _mydb->open();
    QSqlQuery query;
    QList<Question> questionsList;
    if(!_mydb->isOpen()){
        qDebug()<<"Not connected to db";
        return questionsList;
    }

    query.prepare("SELECT * FROM question WHERE anatomyimage_fk = :id");
    query.bindValue(":id", id);
   // query.prepare("SELECT * FROM question WHERE anatomyimage_fk = "+QString::number(id));
    if(query.exec()){
        Question item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setAnatomyimageId(query.value(2).toInt());
            questionsList.append(item);
        }
    }
    qDebug()<<query.lastError().text();

    return questionsList;
}

bool DAOQuestionSQLITE::isOkToPersist(Question *question)
{
    return(!(question->description().isNull() || question->description().isEmpty()));
}
