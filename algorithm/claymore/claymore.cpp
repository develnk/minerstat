#include "claymore.h"
#include "settings.h"
#include "common.h"
#include <QtCore>
#include <QTimer>
#include "loganalitic.h"

Claymore::Claymore(QObject *parent) : QObject(parent){}

Claymore::~Claymore()
{
  disconnect(this, SLOT(getDataTCP()));
  disconnect(this, SLOT(getDataLogs()));
}

bool Claymore::checkSettings()
{
  bool result = true;
  if (settings.getMinerDirectory() == "") {
      qDebug() << tr("Miner Directory is not set.");
      result = false;
  }
  else if (settings.getRemotePort() == 0) {
      qDebug() << tr("The remote port is not set.");
      result = false;
  }

  // @TODO create checking available remote port!

  return result;
}

void Claymore::startAlgorithm()
{
  if (checkSettings()) {
      timer = new QTimer(this);
      connect(timer, &QTimer::timeout, this, &Claymore::executeAlgorithm);
      timer->start(20000);
  }
}

/**
 * Retrieve data to server.
 *
 * @brief Claymore::sendData
 */
void Claymore::sendData()
{

}

/**
 * Slot to get total info from miner client.
 *
 * @brief Claymore::getDataTCP
 */
void Claymore::getDataTCP()
{
  dataTCP.append(tcpRequest->getData());
  qDebug() << "TCP DATA Received:" << dataTCP;
}

/**
 * Slot to get data from logs.
 *
 * @brief Claymore::getDataLogs
 */
void Claymore::getDataLogs()
{
  QStringList tmp = logs->getData();
  for (QStringList::iterator it = tmp.begin(); it != tmp.end(); ++it) {
    QString current = *it;
    dataLogs.append(current.toUtf8());
  }
  qDebug() << "Logs DATA Received:" << dataLogs;
}

void Claymore::executeAlgorithm()
{
  tcpRequest = QSharedPointer<TCPRequest>(new TCPRequest());
  logs = QSharedPointer<logAnalitic>(new logAnalitic());
  connect_from_pointer(tcpRequest, &TCPRequest::dataReady, this, &Claymore::getDataTCP, Qt::DirectConnection);
  connect_from_pointer(logs, SIGNAL(dataReady()), this, SLOT(getDataLogs()), Qt::DirectConnection);
  tcpRequest->start();
  logs->start();
  // If all data gotten.
  sendData();
}
