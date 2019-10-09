#include "mythread.h"
#include <QTime>
#include <QLabel>

MyThread::MyThread(QLabel* title, QObject *parent)
    :QThread(parent)
    ,title(title)
{

}

void sleep(int sec)
{
    QTime dieTime= QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime);
}

void MyThread::run()
{
    title->setText("Running...");
    sleep(3);
    title->setText("50% done...");
    sleep(3);
    title->setText("100% done...");
}
