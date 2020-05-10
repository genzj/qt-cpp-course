#include "worker.h"
#include <QTcpSocket>
#include <QString>
#include <QHostAddress>

Worker::Worker(QTcpSocket* client):client(client)
{
    client->setParent(this);
    connect(client, &QTcpSocket::readyRead, this, &Worker::incomingMessage);
    connect(client, &QTcpSocket::disconnected, this, &Worker::close);
}


void Worker::incomingMessage()
{
    QByteArray msg = client->readAll();
    if (msg.length() == 0 || msg.endsWith(0x04)) {
        client->disconnectFromHost();
    } else {
        client->write(msg);
        emit progress(QString("message received from %1:%2: %3").arg(
            client->peerAddress().toString()
        ).arg(
            client->peerPort()
        ).arg(
            QString(msg)
        ));
    }
}

void Worker::close()
{
    if (client == nullptr) {
        return;
    }
    emit progress(QString("%1:%2 disconnected").arg(
        client->peerAddress().toString()
    ).arg(
        client->peerPort()
    ));
    client->deleteLater();
    client = nullptr;
    deleteLater();
    emit closed();
}
