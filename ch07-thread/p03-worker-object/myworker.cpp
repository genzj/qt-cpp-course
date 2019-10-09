#include "myworker.h"
#include <QTime>
#include <QtDebug>

MyWorker::MyWorker(QObject *parent) : QObject(parent)
{

}

MyWorker::~MyWorker()
{
    qDebug() << "worker destroyed";
}

void sleep(int sec)
{
    QTime dieTime= QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime);
}

void MyWorker::run()
{
    sleep(3);
    emit progressed(50);
    sleep(3);
    emit progressed(100);
}

void MyWorker::start()
{
    emit started();
    run();
    emit finished();
}
