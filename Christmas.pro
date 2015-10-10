#-------------------------------------------------
#
# Project created by QtCreator 2014-12-19T16:58:45
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Christmas
TEMPLATE = app


SOURCES += main.cpp\
        christmas.cpp \
    christmastree.cpp \
    snow.cpp \
    star.cpp \
    staronthetree.cpp

HEADERS  += christmas.h \
    christmastree.h \
    snow.h \
    star.h \
    staronthetree.h

RESOURCES += \
    pix.qrc

DISTFILES += \
    tubiao.rc

RC_FILE    += \
    tubiao.rc
