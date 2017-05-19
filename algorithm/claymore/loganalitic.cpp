#include "loganalitic.h"
#include "settings.h"
#include <QtDebug>

logAnalitic::logAnalitic(QObject *parent) : QObject(parent)
{

}

logAnalitic::~logAnalitic()
{
  settings.setLastLogLineNumber(lastLineNumber);
}

QStringList logAnalitic::getData()
{
  return toSend;
}

void logAnalitic::start()
{
  fileLines.clear();
  listFiles.clear();
  directory = QDir(settings.getMinerDirectory());
  directory.setSorting(QDir::Time);
  listFiles = directory.entryList(QStringList() << "*_log.txt", QDir::Files);
  findLastFile();
  lastLineNumber = (settings.getLastLogLineNumber() > 0) ? settings.getLastLogLineNumber() : 0;
  readFile();
}

void logAnalitic::findLastFile()
{
  QString oldLastLogFile = settings.getLastLogFileName();
  lastFile = listFiles.first();
  if (oldLastLogFile != lastFile) {
    settings.setLastLogLineNumber(0);
  }
  settings.setLastLogFileName(lastFile);
}

void logAnalitic::readFile()
{
  QFile file(directory.absoluteFilePath(lastFile));
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      QString line;
      int line_count = 0;
      QTextStream in(&file);
      while( !in.atEnd())
      {
          line = in.readLine();
          if (++line_count > lastLineNumber) {
              fileLines << line;
              lastLineNumber = line_count;
          }
      }
//      qDebug() << "File Count:" << line_count;
//      qDebug() << "Last line number:" << lastLineNumber;
      settings.setLastLogLineNumber(lastLineNumber);
  }
  file.close();
  parseFile();
}

void logAnalitic::parseFile()
{
  toSend = fileLines.filter("SHARE FOUND");
  emit dataReady();
}
