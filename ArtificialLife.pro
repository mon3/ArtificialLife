#-------------------------------------------------
#
# Project created by QtCreator 2017-04-07T21:03:34
#
#-------------------------------------------------

QT       += core gui

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


SOURCES += main.cpp\
        mainwindow.cpp \
    creature.cpp \
    plant.cpp \
    animal.cpp \
    herbvorous.cpp \
    predator.cpp \
    grid.cpp \
    parametersset.cpp \
    food.cpp

HEADERS  += mainwindow.h \
    creature.h \
    plant.h \
    animal.h \
    herbvorous.h \
    predator.h \
    grid.h \
    parametersset.h \
    food.h

FORMS    += mainwindow.ui



win32:CONFIG(release, debug|release): LIBS += -LE:/boost_1_64_0/lib64-msvc-14.1/ -llibboost_unit_test_framework-vc141-mt-1_64
else:win32:CONFIG(debug, debug|release): LIBS += -LE:/boost_1_64_0/lib64-msvc-14.1/ -llibboost_unit_test_framework-vc141-mt-1_64d
else:unix:!macx: LIBS += -LE:/boost_1_64_0/lib64-msvc-14.1/ -llibboost_unit_test_framework-vc141-mt-1_64

INCLUDEPATH += E:/boost_1_64_0/lib64-msvc-14.1
DEPENDPATH += E:/boost_1_64_0/lib64-msvc-14.1

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += E:/boost_1_64_0/lib64-msvc-14.1/liblibboost_unit_test_framework-vc141-mt-1_64.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += E:/boost_1_64_0/lib64-msvc-14.1/liblibboost_unit_test_framework-vc141-mt-1_64d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += E:/boost_1_64_0/lib64-msvc-14.1/libboost_unit_test_framework-vc141-mt-1_64.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += E:/boost_1_64_0/lib64-msvc-14.1/libboost_unit_test_framework-vc141-mt-1_64d.lib
else:unix:!macx: PRE_TARGETDEPS += E:/boost_1_64_0/lib64-msvc-14.1/liblibboost_unit_test_framework-vc141-mt-1_64.a
