#-------------------------------------------------
#
# Project created by QtCreator 2014-04-27T01:39:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QT += network


TARGET = ULTRON
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    downloader.cpp

HEADERS  += mainwindow.h \
    downloader.h

FORMS    += mainwindow.ui
