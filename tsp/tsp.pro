#-------------------------------------------------
#
# Project created by QtCreator 2013-03-23T00:41:58
#
#-------------------------------------------------

QT       += core gui
#QMAKE_CXXFLAGS += -fopenmp
#QMAKE_LFLAGS += -fopenmp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tsp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    algGen.cpp \
    chemin.cpp \
    crodpx.cpp \
    cropmx.cpp \
    foncAux.cpp \
    ville.cpp

HEADERS  += mainwindow.h \
    algGen.h \
    chemin.h \
    crodpx.h \
    cropmx.h \
    foncAux.h \
    ville.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    tsp.pro.user
