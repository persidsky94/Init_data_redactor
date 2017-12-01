#-------------------------------------------------
#
# Project created by QtCreator 2017-04-10T21:38:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MoveGraphicsItem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    moveitem.cpp \
    mainwindow.cpp \
    gridscene.cpp \
    sourceitem.cpp \
    vertexitem.cpp \
    polygonitem.cpp \
    recievergroup.cpp \
    vertexeditor.cpp \
    polygoneditor.cpp \
    editorsmanager.cpp \
    sourceinfo.cpp \
    sourceeditor.cpp \
    recievergroupinfo.cpp \
    recievergroupeditor.cpp

HEADERS  += \
    moveitem.h \
    mainwindow.h \
    gridscene.h \
    sourceitem.h \
    vertexitem.h \
    polygonitem.h \
    recievergroupparams.h \
    recievergroup.h \
    sourceparams.h \
    vertexparams.h \
    polygonparams.h \
    vertexeditor.h \
    polygoneditor.h \
    editorsmanager.h \
    sourceinfo.h \
    sourceeditor.h \
    recievergroupinfo.h \
    recievergroupeditor.h

FORMS    += \
    mainwindow.ui \
    vertexeditor.ui \
    polygoneditor.ui \
    sourceinfo.ui \
    recievergroupinfo.ui
