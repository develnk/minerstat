#ifndef SETTINGS_H
#define SETTINGS_H

#include "usingleton.h"

#include <QString>

class   Settings;
#define settings Settings::instance()

class Settings: public uSingleton<Settings>
{
public:
  Settings();

  int getRemotePort();
  void setRemotePort(int value);

  QString getMinerDirectory();
  void setMinerDirectory(QString);

  bool getLogsFlag();
  void setLogsFlag(bool value);

  bool getRecentStat();
  void setRecentStat(bool value);

  QString getMinerVersion();
  void setMinerVersion(QString);

  QString getLastLogFileName() const;
  void setLastLogFileName(const QString &value);

  qint64 getLastLogLineNumber() const;
  void setLastLogLineNumber(const qint64 &value);

private:
  int remotePort = 0;
  QString minerDirectory = "";
  bool logsFlag = false;
  bool recentStat = false;
  QString minerVersion = "";
  QString lastLogFileName = "";
  qint64 lastLogLineNumber = 0;
};

#endif // SETTINGS_H
