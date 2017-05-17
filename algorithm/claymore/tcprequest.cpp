#include "tcprequest.h"
#include <QHostAddress>
#include <QAbstractSocket>

TCPRequest::TCPRequest(QObject *parent): QObject(parent), tcpSocket(new QTcpSocket(this))
{
  QDataStream in(tcpSocket);
  in.setVersion(QDataStream::Qt_5_8);
  connect(tcpSocket, &QTcpSocket::connected, this, &TCPRequest::newRequest);
  connect(tcpSocket, &QTcpSocket::readyRead, this, &TCPRequest::read);
  typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
  connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &TCPRequest::displayError);
  QHostAddress hostAddr("127.0.0.1");
  quint16 port = 3333;
  tcpSocket->connectToHost(hostAddr, port);
}

TCPRequest::~TCPRequest()
{
  tcpSocket->disconnect();
}

QByteArray TCPRequest::getData()
{
  return data;
}

void TCPRequest::read()
{
  _blockSize = tcpSocket->bytesAvailable();
  if (_blockSize < 100) {
      return;
  }

  data = tcpSocket->readAll();
  qDebug() << data;
  emit dataReady();
}

void TCPRequest::newRequest()
{
  qDebug() << "Send";
  QString s = QString("{\"id\":0,\"jsonrpc\":\"2.0\",\"method\":\"miner_getstat1\"}");
  QByteArray data = s.toUtf8();
  tcpSocket->write(data, data.size());
}

void TCPRequest::displayError(QAbstractSocket::SocketError socketError)
{
  switch (socketError) {
  case QAbstractSocket::RemoteHostClosedError:
      break;
  case QAbstractSocket::HostNotFoundError:
      qDebug() << "The host was not found. Please check the host name and port settings.";
      break;
  case QAbstractSocket::ConnectionRefusedError:
      qDebug() << "The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.";
      break;
  default:
      qDebug() << tr("The following error occurred: %1.").arg(tcpSocket->errorString());
  }
}
