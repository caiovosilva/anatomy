#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_init_clicked();

    void on_importPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QJsonDocument loadJson(QString &fileName);
    bool saveAssignmentFromJSON(QJsonObject jsonObject);

};

#endif // MAINWINDOW_H
