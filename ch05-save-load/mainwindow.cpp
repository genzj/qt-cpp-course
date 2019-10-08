#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mTasks()
    , keyCtrlA(new QShortcut(QKeySequence("Ctrl+A"), this))
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(keyCtrlA, &QShortcut::activated, this, &MainWindow::addTask);
    connect(ui->actionOpen, &QAction::triggered, this, [this](){load("tasks.json");});
    connect(ui->actionSave, &QAction::triggered, this, [this](){save("tasks.json");});
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTaskImpl(Task* task)
{
    connect(task, &Task::statusChanged,
            this, &MainWindow::taskStatusChanged);
    connect(task, &Task::removed,
            this, &MainWindow::removeOneTask);
    mTasks.append(task);
    ui->tasksLayout->addWidget(task);
    updateStatus();
}

void MainWindow::addTask()
{
    Task *task = new Task();
    addTaskImpl(task);
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


bool MainWindow::load(const QJsonObject& json)
{
    if (!json.contains("tasks") || !json["tasks"].isArray())
    {
        return false;
    }

    QJsonArray const tasks = json["tasks"].toArray();

    for (auto task : mTasks) {
        ui->tasksLayout->removeWidget(task);
        task->setParent(nullptr);
        delete task;
    }

    this->mTasks.clear();
    this->mTasks.reserve(tasks.size());

    for (int idx=0; idx < tasks.size(); idx++)
    {
        Task* task = new Task();
        if (!task->load(tasks[idx].toObject()))
        {
            delete task;
            return false;
        } else {
            addTaskImpl(task);
        }
    }
    return true;
}


void MainWindow::save(QJsonObject& json) const
{
    QJsonArray tasks;
    for (const auto t : mTasks) {
        QJsonObject task;
        t->save(task);
        tasks.append(task);
    }
    json["tasks"] = tasks;
}

bool MainWindow::load(const QString& filename)
{
    QFile loadFile(filename);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    bool ret = load(loadDoc.object());

    qDebug() << "Loaded tasks" << (ret ? "OK" : "failed");
    return ret;
}


void MainWindow::save(const QString& filename) const
{
    QFile saveFile(filename);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonObject doc;
    save(doc);
    QJsonDocument saveDoc(doc);
    saveFile.write(saveDoc.toJson());
}



