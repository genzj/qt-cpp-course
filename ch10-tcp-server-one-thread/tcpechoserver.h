#ifndef TCPECHOSERVER_H
#define TCPECHOSERVER_H

#include <QMainWindow>

class QTcpServer;
class QThread;

QT_BEGIN_NAMESPACE
namespace Ui { class TCPEchoServer; }
QT_END_NAMESPACE

class TCPEchoServer : public QMainWindow
{
    Q_OBJECT

public:
    TCPEchoServer(QWidget *parent = nullptr);
    ~TCPEchoServer();

protected:
    void startServer();

public slots:
    void incomingConnection();
    void log(QString);

private:
    Ui::TCPEchoServer *ui;
    QTcpServer *server;
    QThread* thread;
};
#endif // TCPECHOSERVER_H
