#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mTasks()
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    Task *task = new Task();
    connect(task, &Task::statusChanged,
            this, &MainWindow::taskStatusChanged);
    connect(task, &Task::removed,
            this, &MainWindow::removeOneTask);
    mTasks.append(task);
    ui->tasksLayout->addWidget(task);
    updateStatus();
}

void MainWindow::removeOneTask(Task* task)
{
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    task->setParent(nullptr);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task*)
{
    updateStatus();
}

void MainWindow::updateStatus()
{
    int completedCount = 0;
    for(auto t : mTasks) {
        if (t->isCompleted()) {
            completedCount++;
        }
    }
    int todoCount = mTasks.size() - completedCount;
    ui->statusLabel->setText(
                QString("Status: %1 todo / %2 completed")
                .arg(todoCount)
                .arg(completedCount)
                );
}


void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    taskStatusChanged();
}
