#ifndef CONNECTIONWORKER_H
#define CONNECTIONWORKER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QRunnable>
#include <QTcpSocket>
#include <QEventLoop>
#include <QFile>

class ConnectionWorker : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit ConnectionWorker(int socketDescriptor,QObject *parent = nullptr);
    ~ConnectionWorker();

    void run() override;

signals:
    void finished();
public slots:
    void handleFile();
    void onDisconnected();
    void onReadyRead();
private:
    std::unique_ptr<QFile>file;
    std::unique_ptr<QEventLoop>loop;
    std::unique_ptr<QTcpSocket> m_socket;

    QByteArray arr;
    int sockfd;
    int last_size;
    int fileSize;
};

#endif // CONNECTIONWORKER_H
