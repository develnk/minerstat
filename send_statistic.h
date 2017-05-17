#ifndef SEND_STATISTIC_H
#define SEND_STATISTIC_H

#include <QObject>

class SendStatistic : public QObject
{
  Q_OBJECT
public:
  explicit SendStatistic(QObject *parent = 0);

signals:

public slots:
};

#endif // SEND_STATISTIC_H