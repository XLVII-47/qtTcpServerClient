#ifndef TCPSOCKETHANDLER_H
#define TCPSOCKETHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QEventLoop>
class TcpSocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocketHandler(QObject *parent = nullptr);
    ~TcpSocketHandler();

    void connectServer(QString hostAddress,quint16 Port);



signals:
    void send();

public slots:
    void send8MByte();
    void onConnected();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket* m_tcpSocket;
    std::unique_ptr<QEventLoop> loop;
    int i=0;
};

#endif // TCPSOCKETHANDLER_H
