#include "settings.h"

Settings::Settings():uSingleton<Settings>(*this){
  remotePort = 0;
  logsFlag = false;
  recentStat = false;
  minerDirectory = QString("");
  minerVersion = QString("");
}

int Settings::getRemotePort()
{
return remotePort;
}

void Settings::setRemotePort(int value)
{
remotePort = value;
}

QString Settings::getMinerDirectory()
{
return minerDirectory;
}

void Settings::setMinerDirectory(QString value)
{
minerDirectory = value;
}

bool Settings::getLogsFlag()
{
return logsFlag;
}

void Settings::setLogsFlag(bool value)
{
  logsFlag = value;
}

bool Settings::getRecentStat()
{
return recentStat;
}

void Settings::setRecentStat(bool value)
{
recentStat = value;
}

QString Settings::getMinerVersion()
{
return minerVersion;
}

void Settings::setMinerVersion(QString value)
{
minerVersion = value;
}
