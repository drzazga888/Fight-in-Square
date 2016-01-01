#-------------------------------------------------
#
# Project created by QtCreator 2015-12-01T00:54:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES +=\
    client.cpp \
    client/mainwindow.cpp \
    shared/Model/Board.cpp \
    shared/Model/Player.cpp \
    shared/Model/Shot.cpp \
    shared/Model/BoardElements/BoardElement.cpp \
    shared/Model/BoardElements/ObstacleBoardElement.cpp \
    shared/Model/Model.cpp \
    client/Game.cpp \
    client/Drawer.cpp \
    client/canvas.cpp \
    client/TcpClient.cpp \
    client/NetworkManager.cpp \
    client/Sprites.cpp \
    shared/PlayerAction.cpp \
    client/animation.cpp

HEADERS  += client/mainwindow.h \
    config.h \
    shared/Frame/Frameable.h \
    shared/Model/Board.h \
    shared/Model/Player.h \
    shared/Model/Shot.h \
    shared/Model/BoardElements/BoardElement.h \
    shared/Model/BoardElements/ObstacleBoardElement.h \
    shared/Model/Model.h \
    client/Game.h \
    client/Drawer.h \
    client/canvas.h \
    shared/Utils/Direction.h \
    client/TcpClient.h \
    client/NetworkManager.h \
    shared/Frame/FrameGiveable.h \
    shared/Frame/FrameApplyable.h \
    client/Sprites.h \
    shared/PlayerAction.h \
    client/animation.h

FORMS    += \
    client/mainwindow.ui
