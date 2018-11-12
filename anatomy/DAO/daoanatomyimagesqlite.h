#ifndef DAOANATOMYIMAGESQLITE_H
#define DAOANATOMYIMAGESQLITE_H

#include "daoanatomyimage.h"
#include "dbconnection.h"
#include "DAO/daoclass.h"

#include <QtSql>

class DAOAnatomyImageSQLITE : public DAOAnatomyImage, public DAOClass
{
    // DAOAnatomyImage interface
public:
    bool addAnatomyImage(AnatomyImage *anatomyImage);
    QList<AnatomyImage> getAllAnatomyImages();
    QList<AnatomyImage> getAllAnatomyImagesByAssignmentId(int id);
//    AnatomyImage getAnatomyImage(int id);
//    bool deleteAnatomyImage(AnatomyImage *anatomyImage);

};

#endif // DAOANATOMYIMAGESQLITE_H
