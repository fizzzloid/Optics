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
	mirror.cpp \
    wall.cpp \
    prism.cpp \
    thin_lense.cpp \
    common_functions.cpp

HEADERS  += mainwindow.h \
    ray.h \
    position.h \
    abstractoptics.h \
    field.h \
    optics.h \
	mirror.h \
    wall.h \
    common_functions.h \
    prism.h \
    thin_lense.h \
    lenses.h
