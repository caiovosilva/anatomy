#ifndef MODALITY_H
#define MODALITY_H

#include <QString>

class Modality
{
public:
    Modality(QString description);
    Modality();
    int getId() const;
    void setId(int value);
    QString getDescription() const;
    void setDescription(const QString &value);

private:
    int _id;
    QString _description;
};

#endif // MODALITY_H
