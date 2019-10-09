#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    worker = new MyThread(ui->label, this);
    connect(worker, &MyThread::started,
            this, [this]() { ui->pushButton->setDisabled(true); });
    connect(worker, &MyThread::finished,
            this, [this]() { ui->pushButton->setDisabled(false); });
}

MainWindow::~MainWindow()
{
    delete worker;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    worker->start();
}
