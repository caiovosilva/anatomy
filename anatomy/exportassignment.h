#ifndef EXPORTASSIGNMENT_H
#define EXPORTASSIGNMENT_H

#include <QDialog>
#include "model/assignment.h"
#include <QJsonObject>

namespace Ui {
class ExportAssignment;
}

class ExportAssignment : public QDialog
{
    Q_OBJECT

public:
    explicit ExportAssignment(QWidget *parent = nullptr);
    ~ExportAssignment();

private slots:
    void on_buttonBox_accepted();
    void on_modalitiesComboBox_currentIndexChanged(int index);
    void on_anatomicalRegionComboBox_currentIndexChanged(int index);
    void on_modalityComboBox_currentIndexChanged(int index);

private:
    Ui::ExportAssignment *ui;
    QJsonArray ConvertAssignmentToJson(Assignment &assignment);
    void DownloadAssignment(QJsonArray);
};

#endif // EXPORTASSIGNMENT_H
