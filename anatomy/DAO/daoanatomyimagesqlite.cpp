#include "daoanatomyimagesqlite.h"
//#include "daoquestionsqlite.h"
//#include "model/question.h"

DAOAnatomyImageSQLITE::DAOAnatomyImageSQLITE()
{
    _mydb = DBConnection::Instance()->Connection();
}

//bool DAOAnatomyImageSQLITE::addAnatomyImage(AnatomyImage *anatomyImage)
//{

//}

QList<AnatomyImage> DAOAnatomyImageSQLITE::getAllAnatomyImages()
{
    QSqlQuery query;
    QList<AnatomyImage> anatomyList;
    //DAOQuestion *questionsDAO = new DAOQuestionSQLITE;
    _mydb->open();
    if(!_mydb->open())
        return anatomyList;
    query.prepare("select * from anatomyimage");
    if(query.exec()){
        AnatomyImage item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setImagePath(query.value(1).toString());
            item.setDescription(query.value(2).toString());
            //item.setQuestionsList(questionsDAO->getQuestionsByAnatomyImageId(item.getId()));
            anatomyList.append(item);
        }
    }
    _mydb->commit();
    _mydb->close();
    return anatomyList;
}

//AnatomyImage DAOAnatomyImageSQLITE::getAnatomyImage(int id)
//{

//}

//bool DAOAnatomyImageSQLITE::deleteAnatomyImage(AnatomyImage *anatomyImage)
//{

//}