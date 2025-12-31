#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QMap>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class TaskType{
    Event,
    Activity
};

struct Task{
   TaskType type;
   QString title;
   QTime startTime;
   QTime endTime;
   bool hasEndTime;
   QString frequency;
   bool completed;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QDate selectedDate;
    QMap<QDate, QList<Task>> tasksByDate;

    int index_task_da_editare = -1;

private slots:
    void onDateClicked(const QDate &date);
    void onSaveTaskClicked();
    void onUpdateTaskClicked();
    void onDeleteTaskClicked();
    void onTableSelectionChanged();
    void onTableItemClicked(QTableWidgetItem *item);

private:
    void refreshTable(const QDate &date);
    bool esisteSovrapposizione(const QDate &date, const QTime &start, const QTime &end);
    void salvaSuFile();
    void caricaDaFile();







};
#endif // MAINWINDOW_H
