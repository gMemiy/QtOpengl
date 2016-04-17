#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T19:48:29
#
#-------------------------------------------------

QT       += core gui opengl

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpenGl
TEMPLATE = app


SOURCES += main.cpp\
    scene.cpp \
    particle.cpp \
    particlesystem.cpp \
    firework.cpp \
    object.cpp \
    cloud.cpp

HEADERS  += scene.h \
    particle.h \
    particlesystem.h \
    firework.h \
    object.h \
    cloud.h
