#include "daoanatomyimagesqlite.h"
//#include "daoquestionsqlite.h"
//#include "model/question.h"

//bool DAOAnatomyImageSQLITE::addAnatomyImage(AnatomyImage *anatomyImage)
//{

//}

QList<AnatomyImage> DAOAnatomyImageSQLITE::getAllAnatomyImages()
{
    QSqlQuery query;
    QList<AnatomyImage> anatomyList;
    //DAOQuestion *questionsDAO = new DAOQuestionSQLITE;
    if(!_mydb->open())
        return anatomyList;
    _mydb->transaction();

    query.prepare("select * from anatomyimage");
    if(query.exec()){
        AnatomyImage item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setImagePath(query.value(1).toString());
            item.setAssignmentId(query.value(2).toInt());
            //item.setQuestionsList(questionsDAO->getQuestionsByAnatomyImageId(item.getId()));
            anatomyList.append(item);
        }
    }
    _mydb->commit();
    return anatomyList;
}

//AnatomyImage DAOAnatomyImageSQLITE::getAnatomyImage(int id)
//{

//}

//bool DAOAnatomyImageSQLITE::deleteAnatomyImage(AnatomyImage *anatomyImage)
//{

//}
