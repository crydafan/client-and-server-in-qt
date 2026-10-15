#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui {
class Server;
}
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server() override;

private:
    Ui::Server *ui;
    QTcpServer *serverSocket = nullptr;
    QVector<QString> randomMessages;

    bool InitializeServer();

private slots:
    void SendRandomMessage();

};
#endif // SERVER_H
