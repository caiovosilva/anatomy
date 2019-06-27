#ifndef ENTRIESWINDOW_H
#define ENTRIESWINDOW_H

#include <QWidget>

namespace Ui {
class EntriesWindow;
}

class EntriesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EntriesWindow(QWidget *parent = 0);
    ~EntriesWindow();

private slots:
    void on_modalityButton_clicked();

    void on_newAnatomicalRegionButton_clicked();

    void on_newAssignmentButton_clicked();

    void on_newQuestionButton_clicked();

private:
    Ui::EntriesWindow *ui;
};

#endif // ENTRIESWINDOW_H
