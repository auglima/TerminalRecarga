QT += core
QT -= gui

CONFIG += c++11

LIBS += -pthread

TARGET = Servidor
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    socket.cpp

HEADERS += \
    socket.h \
    packet.h
