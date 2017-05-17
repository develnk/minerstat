#include "claymore.h"
#include "settings.h"
#include "common.h"
#include <QtCore>
#include <QTimer>

Claymore::Claymore(QObject *parent) : QObject(parent){}

Claymore::~Claymore()
{
  disconnect(this, SLOT(getDataTCP()));
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
      timer->start(1000);
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
 * Get total info from miner client.
 *
 * @brief Claymore::getDataTCP
 */
void Claymore::getDataTCP()
{
  dataTCP.append(tcpRequest->getData());
  qDebug() << "TCP DATA Received:" << dataTCP;
}

void Claymore::executeAlgorithm()
{
  tcpRequest = QSharedPointer<TCPRequest>(new TCPRequest(this));
  my_connect(tcpRequest, SIGNAL(dataReady()), this, SLOT(getDataTCP()));
  logs = QSharedPointer<logAnalitic>(new logAnalitic(this));
  // If all data gotten.
  sendData();
}
