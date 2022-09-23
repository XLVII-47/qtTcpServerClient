#include "tcpsockethandler.h"
#include <QFile>
#include <QDebug>


constexpr const unsigned int CHUNK_SIZE = 80'000'000;


TcpSocketHandler::TcpSocketHandler(QObject *parent)
    : QObject{parent}
{
    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket,&QTcpSocket::connected,this,&TcpSocketHandler::onConnected);
    //connect(m_tcpSocket,&QTcpSocket::readyRead,this,&TcpSocketHandler::onReadyRead);
    connect(m_tcpSocket,&QTcpSocket::disconnected,this,&TcpSocketHandler::onDisconnected);
    connect(this,&TcpSocketHandler::send,this,&TcpSocketHandler::send8MByte);
}

TcpSocketHandler::~TcpSocketHandler()
{
    m_tcpSocket->deleteLater();
}

void TcpSocketHandler::connectServer(QString hostAddress,quint16 Port)
{
    m_tcpSocket->connectToHost(hostAddress,Port);
    if(m_tcpSocket->waitForConnected(5000)){

        emit send();
    }else{
        qDebug()<<"could not connect to server...";
    }
}

void TcpSocketHandler::send8MByte()
{
    srand(time(NULL));
    QByteArray arr;
    auto f = [&arr]{
        int diff = 'Z'-'A';
        for(int i=0;i<CHUNK_SIZE;i++){
            char c = 'A'+(rand() % diff);
            arr.append(c);
        }
    };


    f();

    //send filename which is arr[0]
    m_tcpSocket->write(arr,1);
    m_tcpSocket->waitForReadyRead();
    m_tcpSocket->readAll();

    //send array size which is CHUNK_SIZE
    m_tcpSocket->write(QString::number(CHUNK_SIZE).toStdString().data());
    m_tcpSocket->waitForReadyRead();


    QFile file(QString(arr[0]) +"_client.txt");
    if(!file.open(QIODevice::NewOnly)){;
        qCritical() << "could not open file";
        m_tcpSocket->close();
        m_tcpSocket->waitForDisconnected();
        exit(0);
    }

    file.write(arr);

    loop= std::make_unique<QEventLoop>();


    //write all data
    m_tcpSocket->write(arr);


    loop->exec();

    m_tcpSocket->close();
    exit(0);
}


void TcpSocketHandler::onConnected()
{
    qDebug() << "Client connected...";


}

void TcpSocketHandler::onReadyRead()
{

    //m_tcpSocket->read(1024);
}

void TcpSocketHandler::onDisconnected()
{
    qDebug()<< "Client disconnected";
    loop->quit();


}


