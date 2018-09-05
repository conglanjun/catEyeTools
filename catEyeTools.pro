#-------------------------------------------------
#
# Project created by QtCreator 2018-02-04T12:11:29
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = catEyeTools
TEMPLATE = app


SOURCES += main.cpp\
        cateye.cpp \
    httpfun.cpp \
    suma.cpp

HEADERS  += \
    cateye.h \
    httpfun.h \
    suma.h \
    userinfo.h

FORMS    += cateye.ui
