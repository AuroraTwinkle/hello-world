#-------------------------------------------------
#
# Project created by QtCreator 2017-11-25T14:20:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hello
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newspaper.cpp \
    reader.cpp

HEADERS  += mainwindow.h \
    newspaper.h \
    reader.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
