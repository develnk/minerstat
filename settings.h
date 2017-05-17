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

private:
  int remotePort;
  QString minerDirectory;
  bool logsFlag;
  bool recentStat;
  QString minerVersion;
};

#endif // SETTINGS_H
