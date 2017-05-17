#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T17:17:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++1y

CONFIG += c++14

TARGET = minerstat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    send_statistic.cpp \
    algorithm/claymore/claymore.cpp \
    settings.cpp \
    algorithm/claymore/tcprequest.cpp \
    algorithm/claymore/loganalitic.cpp

HEADERS  += mainwindow.h \
    send_statistic.h \
    algorithm/claymore/claymore.h \
    algorithm/algorithm_interface.h \
    usingleton.h \
    settings.h \
    algorithm/claymore/tcprequest.h \
    common.h \
    algorithm/claymore/loganalitic.h

FORMS    += mainwindow.ui

RESOURCES     = systray.qrc
