#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include <QMessageBox>
#include <question.h>
#include <xmlgenerator.h>

#define SEND_BUFFER_SIZE 4096

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QList<Question *> questions, QObject *parent);
    ~Server();
    void startServer();

signals:
private:

    void sendData(QString str, QTcpSocket *socket);
    void parseCmd(QString cmd, QTcpSocket* socket);
    QString queryConstruct(QString type, QString data);

    QMap<int, QTcpSocket*>* clients;
    QMap<int, QString>* names;
    QMap<int, int>* completed;
    QMap<QTcpSocket*, qint16>* msgSize;
    QTcpServer* listen;
    QString xmlQuestions;
    QList<Question*> questions;

public slots:
    void on_newConnection();
    void on_readyRead();
    void on_Error(QAbstractSocket::SocketError err);
signals:
    void newUser(int id);
    void setName(int id, QString name);
    void setCompleted(int id, int value);
};

#endif // SERVER_H
