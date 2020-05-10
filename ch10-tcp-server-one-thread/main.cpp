#include "tcpechoserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCPEchoServer w;
    w.show();
    return a.exec();
}
