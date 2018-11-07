#ifndef NEWASSIGNMENTWINDOW_H
#define NEWASSIGNMENTWINDOW_H

#include <QWidget>

#include "DAO/daomodality.h"
#include "DAO/daomodalitysqlite.h"
#include "DAO/daoanatomicalregion.h"
#include "DAO/daoanatomicalregionsqlite.h"

namespace Ui {
class NewAssignmentWindow;
}

class NewAssignmentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewAssignmentWindow(QWidget *parent = 0);
    ~NewAssignmentWindow();

private slots:
    void on_findFileButton_clicked();

    void on_modalityComboBox_currentIndexChanged(int index);

private:
    Ui::NewAssignmentWindow *ui;
    QStringList anatomyImagesPath;
};

#endif // NEWASSIGNMENTWINDOW_H
