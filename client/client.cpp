#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    clientSocket = new QTcpSocket(this);

    in.setDevice(clientSocket);

    connect(ui->pushButtonForClose, &QAbstractButton::clicked, this, &QWidget::close);
    connect(ui->pushButtonForRequest, &QAbstractButton::clicked, this, &Client::RequestMessage);
    connect(clientSocket, &QAbstractSocket::readyRead, this, &Client::ReadMessage);
}

Client::~Client()
{
    delete ui;
}

void Client::RequestMessage()
{
    QString ip = ui->lineEditForIP->text();
    QString port = ui->lineEditForPort->text();

    qDebug() << "IP: " << ip << ", port: " << port;

    clientSocket->connectToHost(ip, port.toInt());
}

void Client::ReadMessage()
{
    in.startTransaction();

    QString message;

    in >> message;

    if (!in.commitTransaction()) {
        qDebug() << "Could not receive data";
        return;
    }

    qDebug() << "Message received: " << message;
    ui->labelForMessage->setText(message);
}
