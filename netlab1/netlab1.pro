#-------------------------------------------------
#
# Project created by QtCreator 2013-04-25T21:14:57
#
#-------------------------------------------------

QT       += core sql network webkit xml webkitwidgets gui widgets
QT       -=

TARGET = netlab1

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    http/htmlpagegetter.cpp \
    processors/processor.cpp \
    model/model.cpp \
    model/innerlinks.cpp \
    model/modellight.cpp \
    model/modellinks.cpp \
    processors/processorlinks.cpp \
    simpletaskrunner.cpp \
    model/modelprintscreen.cpp \
    processors/processorprintscreen.cpp

HEADERS += \
    http/htmlpagegetter.h \
    processors/processor.h \
    model/model.h \
    model/innerlinks.h \
    model/modellight.h \
    model/modellinks.h \
    processors/processorlinks.h \
    simpletaskrunner.h \
    model/modelprintscreen.h \
    processors/processorprintscreen.h
