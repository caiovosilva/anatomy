#ifndef DAOANATOMYIMAGE_H
#define DAOANATOMYIMAGE_H

#include <QObject>
#include <QList>

#include "anatomyimage.h"

class DAOAnatomyImage : public QObject
{
    Q_OBJECT
public:
    explicit DAOAnatomyImage(QObject *parent = nullptr);
    virtual bool addAnatomyImage(AnatomyImage *anatomyImage) = 0;
    virtual QList<AnatomyImage> getAllAnatomyImages() = 0;
    virtual AnatomyImage getAnatomyImage(int id) = 0;
    virtual bool deleteAnatomyImage(AnatomyImage* anatomyImage) = 0;

signals:

public slots:
};

#endif // DAOANATOMYIMAGE_H
