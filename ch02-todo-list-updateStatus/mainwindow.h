#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "task.h"

#include <QMainWindow>
#include <QVector>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::MainWindow *ui;
    QVector<Task*> mTasks;

public slots:
    void addTask();
    void removeOneTask(Task*);
    void taskStatusChanged(Task* = nullptr);
};
#endif // MAINWINDOW_H
