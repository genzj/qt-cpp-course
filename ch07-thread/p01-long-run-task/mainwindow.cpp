#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void sleep(int sec)
{
    QTime dieTime= QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime) {
//        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("Running...");
    sleep(3);
    ui->label->setText("50% done...");
    sleep(3);
    ui->label->setText("100% done...");
}
