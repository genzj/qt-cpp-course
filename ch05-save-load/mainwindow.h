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
    void updateStatus();

    bool load(const QJsonObject& json);
    void save(QJsonObject& json) const;

    bool load(const QString& filename);
    void save(const QString& filename) const;

private:
    Ui::MainWindow *ui;
    QVector<Task*> mTasks;
    QShortcut* keyCtrlA;

protected:
    void addTaskImpl(Task* task);

public slots:
    void addTask();
    void removeOneTask(Task*);
    void taskStatusChanged(Task* = nullptr);
};
#endif // MAINWINDOW_H
