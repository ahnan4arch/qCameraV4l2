#-------------------------------------------------
#
# Project created by QtCreator 2015-06-23T14:41:17
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cameraV4l2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clscamera.cpp

HEADERS  += mainwindow.h \
    clscamera.h

FORMS    += mainwindow.ui
