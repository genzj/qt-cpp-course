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


    // not working for signature incompatibility
//    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::taskStatusChanged);

    // working when taskStatusChanged has default parameter (nullptr)
    connect(ui->addTaskButton, SIGNAL(clicked()), this, SLOT(taskStatusChanged()));

    // working with C++11
//    connect(ui->addTaskButton, &QPushButton::clicked, this, [this]() {this->taskStatusChanged(nullptr);});
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
    connect(task, &Task::removed,
            this, &MainWindow::taskStatusChanged);
    mTasks.append(task);
    ui->tasksLayout->addWidget(task);
}

void MainWindow::removeOneTask(Task* task)
{
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    task->setParent(nullptr);
    // other slot invocations will be cancelled at task instance's deletion
    // deleting a QObject directly/explictly is not a good practice in Qt
//    delete task;
    task->deleteLater();
}

void MainWindow::taskStatusChanged(Task*)
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
