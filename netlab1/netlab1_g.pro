#-------------------------------------------------
#
# Project created by QtCreator 2013-03-24T13:16:58
#
#-------------------------------------------------

QT += core gui sql network webkit widgets xml webkitwidgets

TARGET = netlab1
TEMPLATE = app


SOURCES += \
    main.cpp \
    gui/mainwindow.cpp \
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
    gui/mainwindow.h \
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

FORMS += \
    mainwindow.ui
