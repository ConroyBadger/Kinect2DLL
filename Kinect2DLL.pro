#-------------------------------------------------
#
# Project created by QtCreator 2015-08-04T20:51:16
#
#-------------------------------------------------

QT -= gui

TARGET = Kinect2DLL
TEMPLATE = lib

DEFINES += KINECT2DLL_LIBRARY

SOURCES += kinect2dll.cpp \
           kinect2.cpp

HEADERS += kinect2dll.h\
           kinect2dll_global.h \
           kinect2.h

win32: LIBS += -L$$PWD/ -lKinect20
