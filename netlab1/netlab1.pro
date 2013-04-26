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
    model/modellight.cpp \
    model/modellinks.cpp \
    processors/processorlinks.cpp \
    simpletaskrunner.cpp \
    model/modelprintscreen.cpp \
    processors/processorprintscreen.cpp \
    model/modelinputs.cpp \
    processors/processorinputs.cpp \
    model/modellists.cpp \
    processors/processorlists.cpp \
    processors/processorimages.cpp \
    model/modelimages.cpp

HEADERS += \
    http/htmlpagegetter.h \
    processors/processor.h \
    processors/processorlinks.h \
    processors/processorprintscreen.h \
    processors/processorlists.h \
    model/modellight.h \
    model/modellinks.h \
    model/modelprintscreen.h \
    processors/processorprintscreen.h \
    model/modelinputs.h \
    processors/processorinputs.h \
    model/modellists.h \
    simpletaskrunner.h \
    model/modelimages.h \
    processors/processorimages.h
