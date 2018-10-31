#ifndef DAOANATOMYIMAGESQLITE_H
#define DAOANATOMYIMAGESQLITE_H

#include "daoanatomyimage.h"
#include "dbconnection.h"

#include <QtSql>

class DAOAnatomyImageSQLITE : public DAOAnatomyImage
{
public:
    DAOAnatomyImageSQLITE();

    // DAOAnatomyImage interface
public:
    bool addAnatomyImage(AnatomyImage *anatomyImage);
    QList<AnatomyImage> getAllAnatomyImages();
    AnatomyImage getAnatomyImage(int id);
    bool deleteAnatomyImage(AnatomyImage *anatomyImage);

private:
    QSqlDatabase *_mydb;

};

#endif // DAOANATOMYIMAGESQLITE_H
