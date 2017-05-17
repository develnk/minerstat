#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>

#include "settings.h"

class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_chooseDirectory_clicked();

private:
  Ui::MainWindow *ui;

  void createActions();
  void createTrayIcon();
  void readSettings();
  void writeSettings();
  void createStatusBar();
  void chooseAlgoritm();

  QAction *minimizeAction;
  QAction *maximizeAction;
  QAction *restoreAction;
  QAction *quitAction;
  QSettings m_Settings;
  QLabel *statusLabel;
  QLabel *statusConnect;
  QSystemTrayIcon *trayIcon;
  QMenu *trayIconMenu;

};

#endif // MAINWINDOW_H
