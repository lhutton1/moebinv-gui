#-------------------------------------------------
#
# Project created by QtCreator 2018-07-24T14:41:31
#
#-------------------------------------------------

QT       += core gui help

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

INCLUDEPATH += /usr/local/include $$PWD/include $$PWD/lib/
DEPENDPATH += /usr/local/include $$PWD/include $$PWD/lib/

LIBS += -L/usr/local/lib/ -L/$$PWD/lib/ -lcln -lginac -lcycle -lfigure

# install the documentation files
docs.path = $$OUT_PWD/moebinv-gui.app/Contents/documentation
docs.files = documentation/*

INSTALLS += docs
###########

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/scene.cpp \
        src/labels.cpp \
        src/cyclecontextmenu.cpp \
        src/graphiccycle.cpp \
        src/view.cpp \
        src/point.cpp \
        src/circle.cpp \
        src/line.cpp \
        src/dockwidget.cpp \
        src/menurelationhandler.cpp \
        src/treemodel.cpp \
        src/matrix4dialog.cpp \
        src/matrix8dialog.cpp \
        src/definecycledialog.cpp \
        src/settingsdialog.cpp \
        src/figureundocommand.cpp \
        src/propertiesdialog.cpp \
        src/helpdialog.cpp \
        src/cstyledialog.cpp

HEADERS += \
        include/conf.h \
        include/mainwindow.h \
        include/scene.h \
        include/labels.h \
        include/cyclecontextmenu.h \
        include/graphiccycle.h \
        include/view.h \
        include/point.h \
        include/line.h \
        include/circle.h \
        include/dockwidget.h \
        include/menurelationhandler.h \
        include/treemodel.h \
        include/matrix4dialog.h \
        include/matrix8dialog.h \
        include/definecycledialog.h \
        include/settingsdialog.h \
        include/figureundocommand.h \
        include/propertiesdialog.h \
        include/helpdialog.h \
        include/cstyledialog.h

FORMS += \
        forms/mainwindow.ui \
        forms/matrix4dialog.ui \
        forms/matrix8dialog.ui \
        forms/definecycledialog.ui \
        forms/settingsdialog.ui \
        forms/propertiesdialog.ui \
        forms/helpdialog.ui \
        forms/cstyledialog.ui
