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
    src/RjpClass/rjpshape.cpp

HEADERS  += \
    include/mainwindow.h \
    include/shapelib/shapefil.h \
    include/RjpClass/rjpshape.h

FORMS    += mainwindow.ui
