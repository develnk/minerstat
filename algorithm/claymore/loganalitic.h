#ifndef LOGANALITIC_H
#define LOGANALITIC_H

#include <QDir>
#include <QObject>

class logAnalitic : public QObject
{
  Q_OBJECT

public:
  logAnalitic(QObject *parent = 0);
  virtual ~logAnalitic();
  QStringList getData();
  void start();

signals:
  void dataReady();

private:
  QDir directory;
  QStringList listFiles;
  QStringList fileLines;
  QString lastFile = "";
  qint64 lastLineNumber = 0;
  QStringList toSend;

  void findLastFile();
  void readFile();
  void parseFile();
};

#endif // LOGANALITIC_H
