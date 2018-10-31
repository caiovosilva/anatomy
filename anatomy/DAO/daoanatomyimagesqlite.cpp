#include "daoanatomyimagesqlite.h"
#include "daoquestionsqlite.h"

DAOAnatomyImageSQLITE::DAOAnatomyImageSQLITE()
{
    _mydb = DBConnection::Instance()->Connection();
}

bool DAOAnatomyImageSQLITE::addAnatomyImage(AnatomyImage *anatomyImage)
{

}

QList<AnatomyImage> DAOAnatomyImageSQLITE::getAllAnatomyImages()
{
    _mydb->open();
    QSqlQuery query;
    QList<AnatomyImage> anatomyList;
    DAOQuestion *daoQuestion = new DAOQuestionSQLITE;
    query.prepare("select * from anatomyimages");
    if(query.exec()){
        AnatomyImage item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setDescription(query.value(1).toString());

            QList<Question> questionsList = daoQuestion->getQuestionsByAnatomyImageId(item.getId());
            //item.setQuestionsList();
            anatomyList.append(item);
        }
    }
    return anatomyList;
}

AnatomyImage DAOAnatomyImageSQLITE::getAnatomyImage(int id)
{

}

bool DAOAnatomyImageSQLITE::deleteAnatomyImage(AnatomyImage *anatomyImage)
{

}
