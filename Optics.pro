#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T21:27:47
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Optics
TEMPLATE = app

CONFIG += console

INCLUDEPATH += ./src c:/workspace/libraries/boost

SOURCES += \
    src/main.cpp\
    src/mainwindow.cpp \
    src/ray.cpp \
    src/vector2D.cpp \
    src/field.cpp \
    src/abstractoptics.cpp \
    src/mirror.cpp \
    src/wall.cpp \
    src/prism.cpp \
    src/thin_lense.cpp \
    src/common_functions.cpp \
    src/sphere.cpp \
    src/real_lense.cpp \
    src/circle_mirror.cpp \
    src/ray_options.cpp \
    src/obj_selection_menu.cpp \
    src/optic_options.cpp \
    src/retroplane.cpp

HEADERS  += src/mainwindow.h \
    src/ray.h \
    src/vector2D.h \
    src/abstractoptics.h \
    src/field.h \
    src/optics.h \
    src/mirror.h \
    src/wall.h \
    src/common_functions.h \
    src/prism.h \
    src/thin_lense.h \
    src/lenses.h \
    src/sphere.h \
    src/real_lense.h \
    src/circle_mirror.h \
    src/ray_options.h \
    src/obj_selection_menu.h \
    src/optic_options.h \
    src/retroplane.h

FORMS += \
    src/ray_options.ui \
    src/optic_options.ui
