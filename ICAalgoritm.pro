#-------------------------------------------------
#
# Project created by QtCreator 2017-08-24T19:24:32
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = ICAalgoritm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    empire.cpp \
    fitnessfunction.cpp \
    icalgorithm.cpp \
    icautils.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    empire.h \
    fitnessfunction.h \
    icalgorithm.h \
    icautils.h \
    qcustomplot.h

FORMS    += mainwindow.ui

DISTFILES +=

