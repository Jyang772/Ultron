#-------------------------------------------------
#
# Project created by QtCreator 2014-04-27T01:39:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QT += network


CONFIG += c++11

TARGET = ULTRON
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    steamlog.cpp

HEADERS  += mainwindow.h \
    cookiesHandler.h \
    steamlog.h

FORMS    += mainwindow.ui \
    steamlog.ui
