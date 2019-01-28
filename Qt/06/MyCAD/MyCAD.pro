#-------------------------------------------------
#
# Project created by QtCreator 2019-01-24T10:38:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyCAD
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    framewnd.cpp \
    line.cpp \
    ishape.cpp \
    rect.cpp \
    eclipse.cpp \
    factroy.cpp \
    linefactroy.cpp \
    rectfactroy.cpp \
    settingdlg.cpp \
    imycommand.cpp \
    insertcmd.cpp

HEADERS += \
        mainwindow.h \
    framewnd.h \
    line.h \
    ishape.h \
    rect.h \
    eclipse.h \
    factroy.h \
    linefactroy.h \
    rectfactroy.h \
    settingdlg.h \
    imycommand.h \
    insertcmd.h

FORMS += \
        mainwindow.ui \
    settingdlg.ui

RESOURCES += \
    res.qrc

LIBS += -lgdi32
