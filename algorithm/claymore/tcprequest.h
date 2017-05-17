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
  TCPRequest(QObject *parent);
  virtual ~TCPRequest();
  QByteArray getData();

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
  quint16 _blockSize;
  QByteArray data;
};

#endif // TCPREQUEST_H
