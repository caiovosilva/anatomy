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
    void on_newModalityButton_clicked();

    void on_newAnatomicalRegionButton_clicked();

private:
    Ui::EntriesWindow *ui;
};

#endif // ENTRIESWINDOW_H
