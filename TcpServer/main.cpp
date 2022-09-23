#include <QCoreApplication>
#include "tcpserverhandler.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpServerHandler server;
    return a.exec();
}
