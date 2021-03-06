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
    vector2D.cpp \
    field.cpp \
    abstractoptics.cpp \
	mirror.cpp \
    wall.cpp \
    prism.cpp \
    thin_lense.cpp \
    common_functions.cpp \
    sphere.cpp \
    real_lense.cpp \
    circle_mirror.cpp \
    ray_options.cpp \
    obj_selection_menu.cpp \
    optic_options.cpp

HEADERS  += mainwindow.h \
    ray.h \
	vector2D.h \
    abstractoptics.h \
    field.h \
    optics.h \
	mirror.h \
    wall.h \
    common_functions.h \
    prism.h \
    thin_lense.h \
    lenses.h \
    sphere.h \
    real_lense.h \
    circle_mirror.h \
    ray_options.h \
    obj_selection_menu.h \
    optic_options.h

FORMS += \
    ray_options.ui \
    optic_options.ui
