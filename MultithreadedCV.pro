#-------------------------------------------------
#
# Project created by QtCreator 2018-02-11T14:29:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultithreadedCV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processorthread.cpp \
    pyramidbuild.cpp

HEADERS  += mainwindow.h \
    processorthread.h \
    pyramidbuild.h

FORMS    += mainwindow.ui


unix|win32: LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui
