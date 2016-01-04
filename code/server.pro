#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T22:08:42
#
#-------------------------------------------------

QT       += core gui network
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += \
    server.cpp \
    server/serverwindow.cpp \
    server/Server.cpp \
    shared/Model/Board.cpp \
    shared/Model/Model.cpp \
    shared/Model/Player.cpp \
    shared/Model/Shot.cpp \
    shared/Model/BoardElements/BoardElement.cpp \
    shared/Model/BoardElements/ObstacleBoardElement.cpp \
    server/TcpServer.cpp \
    server/Controller.cpp \
    server/Connection.cpp \
    server/Data.cpp \
    shared/PlayerAction.cpp \
    server/testcontroller.cpp \
    server/loader.cpp

HEADERS  += \
    server/serverwindow.h \
    server/Server.h \
    shared/Frame/Frameable.h \
    shared/Frame/FrameApplyable.h \
    shared/Frame/FrameGiveable.h \
    shared/Utils/Direction.h \
    shared/Model/Board.h \
    shared/Model/Model.h \
    shared/Model/Player.h \
    shared/Model/Shot.h \
    shared/Model/BoardElements/BoardElement.h \
    shared/Model/BoardElements/ObstacleBoardElement.h \
    server/TcpServer.h \
    server/Controller.h \
    server/Connection.h \
    config.h \
    server/Data.h \
    shared/PlayerAction.h \
    testcontroller.h \
    server/loader.h

FORMS    += \
    server/serverwindow.ui
