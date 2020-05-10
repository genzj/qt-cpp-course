#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>


class QTcpSocket;

class Worker: public QObject
{
    Q_OBJECT
public:
    Worker(QTcpSocket* client);

signals:
    void progress(QString msg);
    void closed();

public slots:
    void incomingMessage();
    void close();

private:
    QTcpSocket* client;
};

#endif // WORKER_H
