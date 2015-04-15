#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T21:27:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Optics
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ray.cpp \
    position.cpp \
    field.cpp \
    abstractoptics.cpp \
    thin_linse.cpp \
    mirror.cpp

HEADERS  += mainwindow.h \
    ray.h \
    position.h \
    abstractoptics.h \
    field.h \
    thin_linse.h \
    optics.h \
    linses.h \
    mirror.h
