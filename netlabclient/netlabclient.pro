#-------------------------------------------------
#
# Project created by QtCreator 2013-05-14T18:23:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = netlabclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qftp.cpp \
    qurlinfo.cpp

HEADERS  += mainwindow.h \
    qftp.h \
    qurlinfo.h

FORMS    += mainwindow.ui
