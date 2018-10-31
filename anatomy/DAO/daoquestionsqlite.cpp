#include "daoquestionsqlite.h"
#include "anatomyimage.h"

DAOQuestionSQLITE::DAOQuestionSQLITE()
{

}

bool DAOQuestionSQLITE::addQuestion(Question *question)
{
    if(!isOkToPersist(question))
        return false;
    QSqlQuery query;
    return(query.exec("INSERT INTO question(description, anatomyimage_fk) VALUES ('"
               +question->description()+ ", "+ question->anatomyimageId()+")"));
}

Question DAOQuestionSQLITE::getQuestion(int id)
{

}

bool DAOQuestionSQLITE::deleteQuestion(Question *question)
{

}

QList<Question> DAOQuestionSQLITE::getQuestionsByAnatomyImageId(int id)
{
    QSqlQuery query;
    QList<Question> questionsList;
    if(query.exec("SELECT * FROM questions WHERE anatomyimage_fk = "+id)){
        Question item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());
            item.setAnatomyimageId(query.value(2).toInt());
            questionsList.append(item);
        }
    }
    return questionsList;
}

bool DAOQuestionSQLITE::isOkToPersist(Question *question)
{
    return(!(question->description().isNull() || question->description().isEmpty()));
}
