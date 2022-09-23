#include "tcpserver.h"
#include <QThread>
#include "connectionworker.h"

TcpServer::TcpServer(QObject *parent)
    : QTcpServer{parent}
{

}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    QThread::currentThread()->setObjectName("main");

    qDebug() << "incomingConnection" << QThread::currentThread();
    QThread* thread= new QThread;

    ConnectionWorker* worker = new ConnectionWorker(socketDescriptor);


    worker->moveToThread(thread);

    connect(thread,&QThread::started,worker,&ConnectionWorker::run);
    connect(worker,&ConnectionWorker::finished,thread, &QThread::quit);
    connect(worker,&ConnectionWorker::finished,worker, &ConnectionWorker::deleteLater);
    connect(thread,&QThread::finished,thread,&QThread::deleteLater);
    //connect(thread,&QThread::finished,thread,[]{qDebug()<<"thread is finished";});


    thread->start();
}
