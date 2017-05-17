#ifndef COMMON_H
#define COMMON_H

#include <QSharedPointer>

template<class T> bool
my_connect(const QSharedPointer<T> &sender,
           const char *signal,
           const QObject *receiver,
           const char *method,
           Qt::ConnectionType type = Qt::AutoConnection)
{
    return QObject::connect(sender.data(), signal, receiver, method, type);
}

#endif // COMMON_H
