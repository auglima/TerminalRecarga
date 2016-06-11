QT += core
QT -= gui

CONFIG += c++11

LIBS += -pthread

TARGET = Cliente
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    socket.cpp \
    BlackLib/v3_0/BlackCore.cpp \
    BlackLib/v3_0/BlackGPIO/BlackGPIO.cpp \
    gaveta.cpp

HEADERS += \
    socket.h \
    BlackLib/v3_0/BlackCore.h \
    BlackLib/v3_0/BlackDef.h \
    BlackLib/v3_0/BlackErr.h \
    BlackLib/v3_0/BlackLib.h \
    BlackLib/v3_0/BlackGPIO/BlackGPIO.h \
    gaveta.h \
    packet.h
