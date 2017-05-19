#ifndef TCPREQUEST_H
#define TCPREQUEST_H

#include <QDataStream>
#include <QObject>
#include <QTcpSocket>
#include <QString>

class TCPRequest : public QObject
{
  Q_OBJECT

public:
  TCPRequest(QObject *parent = 0);
  virtual ~TCPRequest();
  QByteArray getData();
  void start();

signals:
  void dataReady();

private slots:
  void read();
  void displayError(QAbstractSocket::SocketError socketError);
  void newRequest();

private:
  QTcpSocket *tcpSocket;
  QString toMessage;
  QString fromMessage;
  qint64 _blockSize;
  QByteArray data;
};

#endif // TCPREQUEST_H
