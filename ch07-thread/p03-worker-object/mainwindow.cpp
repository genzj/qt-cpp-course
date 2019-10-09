#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myworker.h"

#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , thread(new QThread(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    thread->quit();
    thread->wait();
    delete thread;
    delete ui;
}


// read https://doc.qt.io/qt-5/qthread.html#details for another pattern
void MainWindow::on_pushButton_clicked()
{
    MyWorker* worker = new MyWorker();
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &MyWorker::start);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &MyWorker::finished, thread, &QThread::quit);
    connect(worker, &MyWorker::finished, worker, &QObject::deleteLater);

    connect(worker, &MyWorker::started,
            this, [this](){ui->pushButton->setDisabled(true); ui->label->setText("Running...");});
    connect(worker, &MyWorker::progressed,
            this, [this](int percentage){ui->label->setText(QString("%1% done").arg(percentage));});
    connect(worker, &MyWorker::finished,
            this, [this](){ui->pushButton->setDisabled(false);});

    thread->start();
}
