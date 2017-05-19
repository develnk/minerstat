#ifndef CLAYMORE_H
#define CLAYMORE_H

#include <QObject>
#include <QTimer>
#include <QList>
#include "algorithm/algorithm_interface.h"
#include "tcprequest.h"
#include "loganalitic.h"

class Claymore : public QObject, public Algorithm_Interface
{
  Q_OBJECT
public:
  explicit Claymore(QObject *parent = 0);
  virtual ~Claymore();
  bool checkSettings();
  void startAlgorithm();
  void sendData();

signals:

public slots:
  void getDataTCP();
  void getDataLogs();
  void executeAlgorithm();

private:
  QList<QByteArray> dataTCP;
  QList<QByteArray> dataLogs;
  QSharedPointer<TCPRequest> tcpRequest;
  QSharedPointer<logAnalitic> logs;
  logAnalitic *logs2;
  QTimer *timer;
};

#endif // CLAYMORE_H
