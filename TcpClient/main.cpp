#include <QCoreApplication>
#include "tcpsockethandler.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    if(argc < 2){
        qDebug() << "Port is required as a argument";
        return -1;
    }


    QCoreApplication a(argc, argv);

    TcpSocketHandler socket;



    socket.connectServer("127.0.0.1",atoi(argv[1]));
    QCoreApplication::quit();
    return a.exec();;
}
