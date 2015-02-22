#include "server.h"

Server::Server(QList<Question *> questions, QObject *parent) : QObject(parent)
{
    this->clients = new QMap<int, QTcpSocket*>();
    this->names = new QMap<int, QString>();
    this->completed = new QMap<int, int>();
    this->msgSize = new QMap<QTcpSocket*, qint16>();
    this->questions = questions;
    XMLGenerator* gen = new XMLGenerator();
    this->xmlQuestions = gen->start(questions, false);
}

Server::~Server()
{

}

void Server::startServer()
{
    this->listen = new QTcpServer();
    this->listen->listen(QHostAddress::LocalHost, 12215);
    connect(this->listen, SIGNAL(newConnection()), SLOT(on_newConnection()));
    connect(this->listen, SIGNAL(acceptError(QAbstractSocket::SocketError)),
            SLOT(on_Error(QAbstractSocket::SocketError)));
}

void Server::sendData(QString str, QTcpSocket* socket)
{
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::WriteOnly);
    sendStream.setVersion(QDataStream::Qt_5_0);

    sendStream << quint16(0) << str;
    sendStream.device()->seek(0);
    sendStream << (quint16)(block.size() - sizeof(quint16));
    socket->write(block);
}

void Server::parseCmd(QString cmd, QTcpSocket *socket)
{
    QStringList data = cmd.split('/');
    int id = 0;
    if(data.count() > 3)
    {
        if(data.at(0) != "Tester")
            socket->disconnectFromHost();
        if(data.at(1).toInt() != 0)
            id = data.at(1).toInt();
        if(data.at(2) == "name")
        {
            emit setName(id, data.at(3));
            this->sendData(this->queryConstruct("filelength", QString::number(this->xmlQuestions.length())), socket);
        }
        else if (data.at(2) == "complete")
            emit setCompleted(id, data.at(3).toInt());
        else if (data.at(2) == "file")
        {
            int offset = data.at(3).toInt();
            if((this->xmlQuestions.length() - offset) > SEND_BUFFER_SIZE)
                this->sendData(this->queryConstruct("file",this->xmlQuestions.mid(offset, SEND_BUFFER_SIZE)),socket);
            else
                this->sendData(this->queryConstruct("file",this->xmlQuestions.mid(offset, (this->xmlQuestions.length() - offset))),socket);
        }
        else if (data.at(2) == "result")
        {
            int right = 0;
            QList<QString> userAnswers = data.at(3).split(';');
            for(int i = 0;i<this->questions.count();i++)
            {
                if(this->questions.at(i)->getRightAnswer() == userAnswers.at(i).toInt())
                    right++;
            }
            this->sendData(this->queryConstruct("right", QString::number(right)), socket);
        }
    }
}

QString Server::queryConstruct(QString type, QString data)
{
    return "Tester/"+type+"/"+data;
}

void Server::on_newConnection()
{
    QTcpSocket* client = this->listen->nextPendingConnection();
    this->clients->insert(this->clients->count()+1, client);
    connect(client, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(on_Error(QAbstractSocket::SocketError)));

    this->sendData(this->queryConstruct("setid", QString::number(this->clients->count())), client);
}

void Server::on_readyRead()
{
    QTcpSocket* client = (QTcpSocket*)sender();
    QString buff;
    QDataStream stream(client);
    stream.setVersion(QDataStream::Qt_5_0);
    qint16 local_msgSize = this->msgSize->value(client, 0);

    while(true) {
        if (!local_msgSize) {
            if (client->bytesAvailable() < sizeof(qint16))
                break;
            stream >> local_msgSize;
        }
        if (client->bytesAvailable() < local_msgSize)
            break;
        stream >> buff;
        local_msgSize = 0;
    }
    this->parseCmd(buff, client);
    this->msgSize->insert(client, local_msgSize);
}

void Server::on_Error(QAbstractSocket::SocketError err)
{
    QMessageBox::critical(0, "Ошибка", "Внутренняя ошибка сервера. Name: "+sender()->objectName());
}

