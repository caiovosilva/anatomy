#ifndef DAOANATOMYIMAGE_H
#define DAOANATOMYIMAGE_H

#include <QList>

#include "model/anatomyimage.h"

class DAOAnatomyImage
{
public:
    virtual QList<AnatomyImage> getAllAnatomyImages() = 0;
    virtual bool addAnatomyImage(AnatomyImage *anatomyImage) = 0;
    virtual QList<AnatomyImage> getAllAnatomyImagesByAssignmentId(int id) = 0;
    virtual bool deleteAnatomyImagesByAssignmentId(int id) = 0;
    virtual bool deleteAnatomyImage(int id) = 0;
    virtual ~DAOAnatomyImage(){ }
};

#endif // DAOANATOMYIMAGE_H
