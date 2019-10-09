#ifndef MYTASK_H
#define MYTASK_H

#include "mytasksignals.h"

#include <QRunnable>

class MyTask : public QRunnable
{
public:
    MyTask();
    ~MyTask();

    MyTaskSignals *get_signals() { return &task_signals; }

    void run() override;
private:
    MyTaskSignals task_signals;
};

#endif // MYTASK_H
