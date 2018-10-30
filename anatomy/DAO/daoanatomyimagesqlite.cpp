#include "daoanatomyimagesqlite.h"

DAOAnatomyImageSQLITE::DAOAnatomyImageSQLITE()
{
    _mydb = DBConnection::Instance()->Connection();
}

bool DAOAnatomyImageSQLITE::addAnatomyImage(AnatomyImage *anatomyImage)
{

}

QList<AnatomyImage> DAOAnatomyImageSQLITE::getAllAnatomyImages()
{

}

AnatomyImage DAOAnatomyImageSQLITE::getAnatomyImage(int id)
{

}

bool DAOAnatomyImageSQLITE::deleteAnatomyImage(AnatomyImage *anatomyImage)
{

}
