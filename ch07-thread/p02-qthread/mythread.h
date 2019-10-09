#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class QLabel;


class MyThread : public QThread
{
public:
    MyThread(QLabel* title, QObject *parent = nullptr);

protected:
    void run() override;

private:
    QLabel* title;
};

#endif // MYTHREAD_H
