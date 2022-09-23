#ifndef TCPSERVERHANDLER_H
#define TCPSERVERHANDLER_H

#include <QObject>
#include <QTcpServer>

constexpr const int SERVER_PORT_COUNT=2;


class TcpServerHandler : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerHandler(QObject *parent = nullptr);

signals:

private:
    QTcpServer * m_serverSocket[SERVER_PORT_COUNT];
};

#endif // TCPSERVERHANDLER_H
