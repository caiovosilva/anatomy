#include "daoanatomyimagesqlite.h"
//#include "daoquestionsqlite.h"
//#include "model/question.h"

bool DAOAnatomyImageSQLITE::addAnatomyImage(AnatomyImage *anatomyImage)
{
    if(!_mydb->isOpen())
        return false;
    _mydb->transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO anatomyImage (imagePath, assignment_fk) VALUES (:imagePath, :assignment_fk)");
    query.bindValue(":imagePath", anatomyImage->imagePath());
    query.bindValue(":assignment_fk", anatomyImage->assignmentId());

    bool result = query.exec();
    _mydb->commit();
    return result;
}

QList<AnatomyImage> DAOAnatomyImageSQLITE::getAllAnatomyImages()
{
    QSqlQuery query;
    QList<AnatomyImage> anatomyList;
    if(!_mydb->open())
        return anatomyList;
    _mydb->transaction();

    query.prepare("SELECT * FROM anatomyimage");
    if(query.exec()){
        AnatomyImage item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setImagePath(query.value(1).toString());
            item.setAssignmentId(query.value(2).toInt());
            anatomyList.append(item);
        }
    }
    _mydb->commit();
    return anatomyList;
}

QList<AnatomyImage> DAOAnatomyImageSQLITE::getAllAnatomyImagesByAssignmentId(int id)
{
    QSqlQuery query;
    QList<AnatomyImage> anatomyList;
    if(!_mydb->open())
        return anatomyList;
    _mydb->transaction();

    query.prepare("SELECT * FROM anatomyimage WHERE assignment_fk = :assignment_fk");
    query.bindValue(":assignment_fk", id);

    if(query.exec()){
        AnatomyImage item;
        while(query.next()){
            item.setId(query.value(0).toInt());
            item.setImagePath(query.value(1).toString());
            item.setAssignmentId(query.value(2).toInt());
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
