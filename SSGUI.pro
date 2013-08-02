#-------------------------------------------------
#
# Project created by QtCreator 2013-08-02T16:39:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SSGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sswraper.cpp \
    ssresultmodel.cpp

HEADERS  += mainwindow.h \
    sswraper.h \
    ssresultmodel.h

FORMS    += mainwindow.ui
