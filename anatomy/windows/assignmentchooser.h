#ifndef ASSIGNMENTCHOOSER_H
#define ASSIGNMENTCHOOSER_H

#include <QDialog>

namespace Ui {
class AssignmentChooser;
}

class AssignmentChooser : public QDialog
{
    Q_OBJECT

public:
    explicit AssignmentChooser(QWidget *parent = 0);
    ~AssignmentChooser();

private slots:
    void on_modalitiesComboBox_currentIndexChanged(int index);

    void on_anatomicalRegionComboBox_currentIndexChanged(int index);

    void on_buttonBox_accepted();

private:
    Ui::AssignmentChooser *ui;
};

#endif // ASSIGNMENTCHOOSER_H
