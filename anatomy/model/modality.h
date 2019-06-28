#ifndef MODALITY_H
#define MODALITY_H

#include <QString>

class Modality
{
public:
    Modality(QString description);
    Modality(QString description, int id);
    Modality();
    ~Modality();

    int id() const;
    void setId(int value);

    QString description() const;
    void setDescription(const QString &value);

private:
    int _id;
    QString _description;
};

#endif // MODALITY_H
