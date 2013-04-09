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
    model/model.cpp \
    sql/sqlitecontroller.cpp \
    sql/dbrecord.cpp \
    model/serializer.cpp

HEADERS += \
    gui/mainwindow.h \
    http/htmlpagegetter.h \
    processors/processor.h \
    model/model.h \
    sql/sqlitecontroller.h \
    sql/dbrecord.h \
    model/serializer.h

FORMS += \
    mainwindow.ui
