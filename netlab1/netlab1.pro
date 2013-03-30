#-------------------------------------------------
#
# Project created by QtCreator 2013-03-24T13:16:58
#
#-------------------------------------------------

QT += core gui sql network webkit

TARGET = netlab1
TEMPLATE = app


SOURCES += \
    main.cpp \
    gui/mainwindow.cpp \
    http/htmlpagegetter.cpp \
    processors/processor.cpp \
    model/model.cpp

HEADERS += \
    gui/mainwindow.h \
    http/htmlpagegetter.h \
    processors/processor.h \
    model/model.h

FORMS += \
    mainwindow.ui
