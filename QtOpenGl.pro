#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T19:48:29
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpenGl
TEMPLATE = app


SOURCES += main.cpp\
    scene.cpp \
    particle.cpp \
    particlesystem.cpp

HEADERS  += scene.h \
    particle.h \
    particlesystem.h
