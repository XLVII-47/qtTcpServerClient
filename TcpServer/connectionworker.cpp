#include "connectionworker.h"
#include <QDebug>

constexpr const unsigned int XSEC= 1;

ConnectionWorker::ConnectionWorker(int socketDescriptor,QObject *parent)
    : QObject{parent},sockfd{socketDescriptor},last_size{0}
{
}




ConnectionWorker::~ConnectionWorker()
{
    qDebug() << "Destructor ConnectionWorker.. quit from thread " <<QThread::currentThread();

    if(m_socket->isOpen()){
        m_socket->close();

    }

    if(file->isOpen()){
        file->close();
    }
}


void ConnectionWorker::run()
{

    //SOCKET
    m_socket =std::make_unique<QTcpSocket>();

    if (!m_socket->setSocketDescriptor(sockfd)) {
        qDebug() << "Error setSocketDescriptor";
        return;
    }

    connect(m_socket.get(),&QTcpSocket::connected,this,&ConnectionWorker::onReadyRead,Qt::DirectConnection);
    connect(m_socket.get(),&QTcpSocket::disconnected,this,&ConnectionWorker::onDisconnected,Qt::DirectConnection);


    m_socket->waitForReadyRead();
    auto file_id = m_socket->readLine();

    qDebug() << "file_id" <<file_id<< QThread::currentThread();
    m_socket->write("xx");//write dump value for comm
    m_socket->waitForReadyRead();

    fileSize = m_socket->readLine().toInt();
    qDebug() << "file_size" <<fileSize<< QThread::currentThread();
    m_socket->write("xx");//write dump value for comm
    m_socket->waitForBytesWritten();

    connect(m_socket.get(),&QTcpSocket::readyRead,this,&ConnectionWorker::onReadyRead,Qt::DirectConnection);


    //FILE
    file = std::make_unique<QFile>(QString(file_id)+"_server.txt");
    if(!file->open(QIODevice::NewOnly)){;
        qDebug() << "could not open file";
    }

    //EVENTLOOP
    loop = std::make_unique<QEventLoop>();

    //TIMER
    std::unique_ptr<QTimer> timer(new QTimer());
    connect(timer.get(), &QTimer::timeout, this, &ConnectionWorker::handleFile);
    timer->start(XSEC * 1000);


    loop->exec();

    emit finished();

}


void ConnectionWorker::handleFile()
{
    if(last_size<fileSize)
    {
        qDebug() << "Handling file.... " << "Thread : "<< QThread::currentThread();
        qDebug() << arr.size() <<"Last-size "<<last_size;

        file->write(arr.data()+last_size,arr.size()-last_size);
        file->flush();
        last_size=arr.size();

    }else{//close socket when last byte is written
        if(m_socket->isOpen()){
            m_socket->close();
        }
    }
}


void ConnectionWorker::onDisconnected()
{
    qDebug() << "Disconnecting.... " << "Thread : "<< QThread::currentThread();

    loop->quit();

}

void ConnectionWorker::onReadyRead()
{
    while(m_socket->bytesAvailable() > 0)
    {
        arr.append(m_socket->readAll());
        qDebug() <<"Thread : "<< QThread::currentThread()<<"Read size : " <<arr.size() << " " <<"Port : " <<m_socket->localPort() ;
        m_socket->flush();
    }
}
