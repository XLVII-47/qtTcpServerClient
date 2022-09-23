#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // TCPSERVER_H
