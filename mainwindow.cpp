#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithm/claymore/claymore.h"

#include <QtCore>
#include <QtGui>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->remotePort->setValidator( new QIntValidator(1, 65535, this) );
  createActions();
  createTrayIcon();
  readSettings();
  createStatusBar();
  chooseAlgoritm();

  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
  writeSettings();
  delete ui;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason) {
  case QSystemTrayIcon::Trigger:
      show();
      break;
  case QSystemTrayIcon::DoubleClick:
      hide();
      break;
  case QSystemTrayIcon::MiddleClick:
      break;
  default:
      ;
  }
}

/**
 * @brief MainWindow::createActions
 */
void MainWindow::createActions()
{
  minimizeAction = new QAction(tr("Mi&nimize"), this);
  connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

  maximizeAction = new QAction(tr("Ma&ximize"), this);
  connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

  restoreAction = new QAction(tr("&Restore"), this);
  connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

  quitAction = new QAction(tr("&Quit"), this);
  connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

/**
 * @brief MainWindow::createTrayIcon
 */
void MainWindow::createTrayIcon()
{
  trayIconMenu = new QMenu(this);
  trayIconMenu->addAction(minimizeAction);
  trayIconMenu->addAction(maximizeAction);
  trayIconMenu->addAction(restoreAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(quitAction);

  trayIcon = new QSystemTrayIcon(this);
  trayIcon->setContextMenu(trayIconMenu);
  QIcon icon(":/images/bad.png");
  trayIcon->setIcon(icon);
  trayIcon->show();
}

/**
 * @brief MainWindow::readSettings
 */
void MainWindow::readSettings()
{
  m_Settings.beginGroup("/Settings");
  int miner_client = m_Settings.value("/miner_client", "").toInt();
  QString client_directory = m_Settings.value("/client_directory", "").toString();
  settings.setMinerDirectory(client_directory);
  int nWidht = m_Settings.value("/widht", width()).toInt();
  int nHeight = m_Settings.value("/height", height()).toInt();
  QString rPort = m_Settings.value("/remote_port", "").toString();
  settings.setRemotePort(rPort.toInt());
  bool logs_flag = m_Settings.value("/logs_flag").toBool();
  settings.setLogsFlag(logs_flag);
  Qt::CheckState lF = Qt::CheckState::Unchecked;
  if (logs_flag == true) {
      lF = Qt::CheckState::Checked;
  }
  bool enableStat = m_Settings.value("/enable_receive_stat").toBool();
  settings.setRecentStat(enableStat);
  Qt::CheckState eS = (enableStat == true) ? Qt::CheckState::Unchecked : Qt::CheckState::Checked;

  ui->directoryInput->setText(client_directory);
  ui->minerClient->setCurrentIndex(miner_client);
  ui->remotePort->setText(rPort);
  ui->logsFlag->setCheckState(lF);
  ui->enableReceiveStat->setCheckState(eS);

  resize(nWidht, nHeight);

  m_Settings.endGroup();
}

/**
 * @brief MainWindow::writeSettings
 */
void MainWindow::writeSettings()
{
  m_Settings.beginGroup("/Settings");
  m_Settings.setValue("/miner_client", ui->minerClient->currentIndex());
  m_Settings.setValue("/client_directory", ui->directoryInput->text());
  m_Settings.setValue("/remote_port", ui->remotePort->text());
  m_Settings.setValue("/logs_flag", ui->logsFlag->checkState());
  m_Settings.setValue("/enable_receive_stat", ui->enableReceiveStat->checkState());
  m_Settings.setValue("/widht", width());
  m_Settings.setValue("/height", height());
  m_Settings.endGroup();
}

void MainWindow::createStatusBar()
{
  statusLabel = new QLabel(this);
  statusConnect = new QLabel(this);

  ui->statusBar->addPermanentWidget(statusLabel, 0);
  ui->statusBar->addPermanentWidget(statusConnect, 1);

  statusLabel->setText("Test Message");
  statusConnect->setText("Connect is ready");
}

void MainWindow::chooseAlgoritm()
{
  int miner = ui->minerClient->currentIndex();
  switch (miner) {
    case 0:
      Claymore *client = new Claymore();
      client->startAlgorithm();
      break;
    }
}

void MainWindow::on_chooseDirectory_clicked()
{
    QString str = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());
    ui->directoryInput->setText(str);
}
