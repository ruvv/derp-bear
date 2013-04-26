#-------------------------------------------------
#
# Project created by QtCreator 2013-03-24T13:16:58
#
#-------------------------------------------------

QT += core gui sql network webkit widgets xml webkitwidgets

TARGET = netlab2
TEMPLATE = app



TEMPLATE = app

SOURCES += \
    main.cpp \
    gui/mainwindow.cpp \
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
    model/modelimages.cpp \
    processors/processorimages.cpp

HEADERS += \
    http/htmlpagegetter.h \
    gui/mainwindow.h \
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

FORMS += \
    mainwindow.ui
