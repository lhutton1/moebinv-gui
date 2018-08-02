#-------------------------------------------------
#
# Project created by QtCreator 2018-07-24T14:41:31
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = moebinv-gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/local/include $$PWD/include
DEPENDPATH += /usr/local/include $$PWD/include

unix: LIBS += -L/usr/local/lib/ -lginac -lcycle -lfigure

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/scene.cpp \
        src/zoom.cpp \
        src/labels.cpp \
        src/point.cpp \
    test.cpp

HEADERS += \
        include/mainwindow.h \
        include/scene.h \
        include/zoom.h \
        include/labels.h \
        include/point.h \
        include/drawingmetric.h \
    test.h

FORMS += \
        forms/mainwindow.ui
