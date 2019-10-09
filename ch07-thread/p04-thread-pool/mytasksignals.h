#ifndef MYTASKSIGNALS_H
#define MYTASKSIGNALS_H

#include <QObject>

class MyTaskSignals : public QObject
{
    Q_OBJECT
public:
    explicit MyTaskSignals(QObject *parent = nullptr);

signals:
    void started();
    void progressed(int percentage);
    void finished();
};

#endif // MYTASKSIGNALS_H
