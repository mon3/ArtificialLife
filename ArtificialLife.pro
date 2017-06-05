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





SOURCES += src/main.cpp\
        src/grid/mainwindow.cpp \
    src/sugarscape/animal.cpp \
    src/grid/grid.cpp \
    src/sugarscape/herbivorous.cpp \
    src/shared/parametersset.cpp \
    src/sugarscape/plant.cpp \
    src/sugarscape/predator.cpp \
    src/sugarscape/being.cpp \
    src/grid/beingwindow.cpp \
    src/evolalg/evolutionaryalg.cpp \
    src/shared/board.cpp \
    src/grid/beingitem.cpp \
    src/shared/board.tpp \
    src/evolalg/reproduction.cpp \
    src/evolalg/meanreproduction.cpp \
    src/evolalg/interpolationreproduction.cpp \
    src/evolalg/generator.cpp \
    src/evolalg/eapopulationinitializer.cpp \
    src/evolalg/eareproductiontype.cpp \
    src/evolalg/eainitializer.cpp

HEADERS  += src/grid/mainwindow.h \
    src/sugarscape/being.h \
    src/sugarscape/animal.h \
    src/grid/grid.h \
    src/sugarscape/herbivorous.h \
    src/shared/parametersset.h \
    src/sugarscape/plant.h \
    src/sugarscape/predator.h \
    src/grid/beingwindow.h \
    src/evolalg/evolutionaryalg.h \
    src/shared/board.h \
    src/grid/beingitem.h \
    src/view/visitor.h \
    src/evolalg/reproduction.h \
    src/evolalg/meanreproduction.h \
    src/evolalg/interpolationreproduction.h \
    src/evolalg/generator.h \
    src/evolalg/eapopulationinitializer.h \
    src/evolalg/eareproductiontype.h \
    src/evolalg/eainitializer.h

FORMS    += src/grid/mainwindow.ui \
    src/grid/beingwindow.ui
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

INCLUDEPATH += E:/boost_1_64_0
