#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class Client;
}
QT_END_NAMESPACE

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client() override;

private:
    Ui::Client *ui;
    QTcpSocket *clientSocket = nullptr;
    QDataStream in;

private slots:
    void RequestMessage();

    void ReadMessage();
};
#endif // CLIENT_H
