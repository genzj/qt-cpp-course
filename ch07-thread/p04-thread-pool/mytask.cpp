#include "mytask.h"

#include <QTime>
#include <QtDebug>

MyTask::MyTask()
{

}

MyTask::~MyTask()
{
    qDebug() << "task destroyed";
}

void sleep(int sec)
{
    QTime dieTime= QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime);
}

void MyTask::run()
{
    emit task_signals.started();
    sleep(3);
    emit task_signals.progressed(50);
    sleep(3);
    emit task_signals.progressed(100);
    emit task_signals.finished();
}
