#ifndef LISTQUESTIONSWINDOW_H
#define LISTQUESTIONSWINDOW_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class ListQuestionsWindow;
}

class ListQuestionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ListQuestionsWindow(QWidget *parent = 0);
    ~ListQuestionsWindow();

private slots:

void cellSelected(int nRow, int nCol);

private:
    QTableWidget* m_pTableWidget;
    QStringList m_TableHeader;
    Ui::ListQuestionsWindow *ui;
};

#endif // LISTQUESTIONSWINDOW_H
