#-------------------------------------------------
#
# Project created by QtCreator 2013-05-05T23:28:30
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = ftp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ftpserver.cpp \
    ftpport.cpp \
    ftpfilesocket.cpp \
    ftplistitem.cpp

HEADERS += \
    ftpserver.h \
    ftpport.h \
    ftpfilesocket.h \
    ftplistitem.h
