#-------------------------------------------------
#
# Project created by QtCreator 2013-10-23T15:57:36
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = omilo-cli-exec
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    downloadmanager.cpp \
    postprocessor.cpp

HEADERS += \
    downloadmanager.h \
    postprocessor.h
