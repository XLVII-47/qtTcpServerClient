#include "tcpserverhandler.h"
#include "tcpserver.h"


constexpr const unsigned int PORT_1=5001;
constexpr const unsigned int PORT_2=6001;


TcpServerHandler::TcpServerHandler(QObject *parent)
    : QObject{parent}
{
    //PREPARE SERVER FOR PORT_1
     m_serverSocket[0] = new TcpServer(this);

 //    connect(m_serverSocket[0],&TcpServer::newConnection,this,&TcpSocketHandler::onNewSocketConnection);

     if(m_serverSocket[0]->listen(QHostAddress::Any,PORT_1)){
         qDebug() << "[+]Server(Port = "<<PORT_1<<") is running!";
     }else{
         qDebug() << "[-]Server(Port = "<<PORT_1<<") unable to start listening for connections!";
     }

    //PREPARE SERVER FOR PORT_2
     m_serverSocket[1] = new TcpServer(this);

 //    connect(m_serverSocket[1],&TcpServer::newConnection,this,&TcpSocketHandler::onNewSocketConnection);

     if(m_serverSocket[1]->listen(QHostAddress::Any,PORT_2)){
         qDebug() << "[+]Server(Port = "<<PORT_2<<") is running!";
     }else{
         qDebug() << "[-]Server(Port = "<<PORT_2<<") unable to start listening for connections!";
     }

}
