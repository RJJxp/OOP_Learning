#-------------------------------------------------
#
# Project created by QtCreator 2018-12-09T16:25:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsm_oop
TEMPLATE = app


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/shapelib/dbfopen.cpp \
    src/shapelib/shpopen.cpp \
    src/shapelib/shptree.cpp \
    src/RjpClass/rjpshape.cpp \
    src/RjpClass/rjpdataset.cpp \
    src/RjpClass/rjpfactory.cpp \
    src/RjpClass/rjpshapes.cpp

HEADERS  += \
    include/mainwindow.h \
    include/shapelib/shapefil.h \
    include/RjpClass/rjpshape.h \
    include/RjpClass/rjpdataset.h \
    include/RjpClass/rjpfactory.h \
    include/RjpClass/rjpshapes.h \
    include/RjpClass/rjpshapescommand.hpp

FORMS    += mainwindow.ui
