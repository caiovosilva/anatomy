#include "daoquestionsqlite.h"

DAOQuestionSQLITE::DAOQuestionSQLITE()
{
    _mydb = DBConnection::Instance()->Connection();
}

bool DAOQuestionSQLITE::addQuestion(Question *question)
{
    _mydb->open();
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO question (description, anatomyimage_fk) "
                  "VALUES (:description, :anatomyimage_fk)");
    query.bindValue(":description", question->description());
    query.bindValue(":anatomyimage_fk", question->anatomyimageId());

    bool result = query.exec();
    question->setId(query.lastInsertId().toInt());
    _mydb->commit();
    _mydb->close();
    return result;
}

//Question DAOQuestionSQLITE::getQuestion(int id)
//{

//}

//bool DAOQuestionSQLITE::deleteQuestion(Question *question)
//{

//}

QList<Question> DAOQuestionSQLITE::getQuestionsByAnatomyImageId(int id)
{
    _mydb->open();
    QSqlQuery query;
    QList<Question> questionsList;
    if(!_mydb->isOpen()){
        qDebug()<<"Not connected to db";
        return questionsList;
    }
    _mydb->transaction();

    query.prepare("SELECT * FROM question WHERE anatomyimage_fk = :id");
    query.bindValue(":id", id);

    if(query.exec()){
        Question item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setAnatomyimageId(query.value(2).toInt());
            questionsList.append(item);
        }
    }
    _mydb->commit();
    _mydb->close();
    return questionsList;
}

bool DAOQuestionSQLITE::updateQuestion(Question *question)
{
    _mydb->open();
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("UPDATE question SET description = :description, anatomyimage_fk = :anatomyimage_fk, "
                  "correctAnswer_fk = :correctAnswer_fk WHERE id = :id");
    query.bindValue(":description", question->description());
    query.bindValue(":anatomyimage_fk", question->anatomyimageId());
    query.bindValue(":correctAnswer_fk", question->correctAnswerId());
    query.bindValue(":id", question->id());

    bool result = query.exec();
    _mydb->commit();
    _mydb->close();
    return result;
}