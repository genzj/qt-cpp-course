#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytask.h"

#include <QThreadPool>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , thread_pool(new QThreadPool(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    thread_pool->clear();
    thread_pool->waitForDone();
    delete thread_pool;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    MyTask* task = new MyTask();

    connect(task->get_signals(), &MyTaskSignals::started,
            this, [this](){ui->pushButton->setDisabled(true); ui->label->setText("Running...");});
    connect(task->get_signals(), &MyTaskSignals::progressed,
            this, [this](int percentage){ui->label->setText(QString("%1% done").arg(percentage));});
    connect(task->get_signals(), &MyTaskSignals::finished,
            this, [this](){ui->pushButton->setDisabled(false);});

    thread_pool->start(task);
}
