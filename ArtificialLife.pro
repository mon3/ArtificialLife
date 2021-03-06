#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T18:10:35
#
#-------------------------------------------------

QT       += core gui
QT       += widgets testlib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArtificialLife
TEMPLATE = app
TEMPLATE = subdirs


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# QT += testlib

SOURCES += main.cpp\
        mainwindow.cpp \
    animal.cpp \
    food.cpp \
    grid.cpp \
    herbivorous.cpp \
    parametersset.cpp \
    plant.cpp \
    predator.cpp \
    being.cpp


HEADERS  += mainwindow.h \
    animal.h \
    food.h \
    grid.h \
    herbivorous.h \
    parametersset.h \
    plant.h \
    predator.h \
    being.h

FORMS    += mainwindow.ui
#CONFIG   += c++11

#unix|macx: QMAKE_CXXFLAGS += -fpermissive
# Compiler options
*-g++* {
  message(Setting flags for GCC or MinGw)

  QMAKE_CXXFLAGS += -Wall
  QMAKE_CXXFLAGS += -Wextra
  QMAKE_CXXFLAGS += -Wpedantic
  QMAKE_CXXFLAGS += -Wno-type-limits
  QMAKE_CXXFLAGS += -Wpedantic


  win32 {
    # Set debug options for MinGw in QtCreator
    QMAKE_CXXFLAGS_DEBUG = -g -O0
  }
}

*-clang* {
  message(Setting flags for clang)
  QMAKE_CXXFLAGS += -stdlib=libc++
}

*-msvc* {
  message(Setting flags for Visual Studio)
  QMAKE_CXXFLAGS_WARN_ON = ""
  QMAKE_CXXFLAGS += /W4
}

SUBDIRS += \
    Tests
