#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    serverSocket = new QTcpServer(this);

    InitializeServer();

    connect(ui->pushButtonForClose, &QAbstractButton::clicked, this, &QWidget::close);
    connect(serverSocket, &QTcpServer::newConnection, this, &Server::SendRandomMessage);
}

Server::~Server()
{
    delete ui;
}

bool Server::InitializeServer()
{
    for (int i = 0; i < 100; ++i) {
        randomMessages << "Random message " + QString::number(i + 1);
    }

    if (!serverSocket->listen()) {
        qDebug() << "Failure in the server: " + serverSocket->errorString();
        return false;
    }

    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();
    qDebug() << ipList;

    QString ip;
    for (int i = 0; i < ipList.capacity(); i++) {
        const QHostAddress &address = ipList.at(i);
        if (address != QHostAddress::LocalHost && address.toIPv4Address()) {
            ip = address.toString();
            break;
        }
    }
    QString port = QString::number(serverSocket->serverPort());
    qDebug() << "IP: " + ip + ", port: " + port;

    ui->labelForIP->setText(ip);
    ui->labelForPort->setText(port);

    return true;
}

void Server::SendRandomMessage()
{
    QString message = randomMessages[QRandomGenerator::global()->bounded(randomMessages.size())];
    qDebug() << message;

    QByteArray byteArray;
    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);
    dataStream << message;

    QTcpSocket *client_socket = serverSocket->nextPendingConnection();
    connect(client_socket, &QAbstractSocket::disconnected, client_socket, &QObject::deleteLater);

    client_socket->write(byteArray);
    client_socket->disconnectFromHost();
}
