#ifndef DAOANATOMYIMAGE_H
#define DAOANATOMYIMAGE_H

#include <QList>

#include "model/anatomyimage.h"

class DAOAnatomyImage
{
public:
    virtual QList<AnatomyImage> getAllAnatomyImages() = 0;
    virtual bool addAnatomyImage(AnatomyImage *anatomyImage) = 0;
//    virtual AnatomyImage getAnatomyImage(int id) = 0;
//    virtual bool deleteAnatomyImage(AnatomyImage* anatomyImage) = 0;

};

#endif // DAOANATOMYIMAGE_H
