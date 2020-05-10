#include "tcpechoserver.h"
#include "ui_tcpechoserver.h"
#include "worker.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QTime>
#include <QThread>
#include <QMessageBox>

TCPEchoServer::TCPEchoServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TCPEchoServer)
    , server(new QTcpServer(this))
{
    thread = new QThread;
    ui->setupUi(this);
    startServer();
    thread->start();
}

TCPEchoServer::~TCPEchoServer()
{
    delete ui;
    server->close();
    server->setParent(nullptr);
    server->deleteLater();
    thread->quit();
    thread->wait(500);
    thread->deleteLater();
}

void TCPEchoServer::startServer()
{
    connect(server, &QTcpServer::newConnection, this, &TCPEchoServer::incomingConnection);
    if (!server->listen(
        QHostAddress::AnyIPv4, 22334
    )) {
        QMessageBox(
                    QMessageBox::Icon::Critical,
                    QString("error"),
                    server->errorString()
        ).exec();
    }

    ui->label->setText(
        QString("Listening at %1:%2").arg(
            server->serverAddress().toString()
        ).arg(
            server->serverPort()
        )
    );
}

void TCPEchoServer::incomingConnection()
{
    if (!server->hasPendingConnections()) {
        return;
    }

    QTcpSocket* client = server->nextPendingConnection();
    log(QString("client %1:%2 connected").arg(
        client->peerAddress().toString()
    ).arg(
        client->peerPort()
    ));
    Worker *worker = new Worker(client);

    connect(thread, &QThread::finished, worker, &Worker::close);
    connect(worker, &Worker::progress, this, &TCPEchoServer::log);
    worker->moveToThread(thread);
}

void TCPEchoServer::log(QString msg)
{
    ui->log->append(
        QString("[%1] %2").arg(
            QTime::currentTime().toString()
        ).arg(
            msg
        )
    );
}
