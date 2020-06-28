#-------------------------------------------------
#
# Project created by QtCreator 2020-06-02T16:05:14
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tower3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    button.cpp \
    gamewindow.cpp \
    tower.cpp \
    enemy.cpp \
    bullet.cpp \
    menu.cpp \
    gameoverwindow.cpp \
    win.cpp \
    button2.cpp \
    enemyintro.cpp \
    towerintro.cpp \
    button3.cpp \
    gamewindow2.cpp

HEADERS += \
        mainwindow.h \
    button.h \
    gamewindow.h \
    tower.h \
    enemy.h \
    bullet.h \
    menu.h \
    gameoverwindow.h \
    win.h \
    button2.h \
    enemyintro.h \
    towerintro.h \
    button3.h \
    gamewindow2.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    cover.qrc \
    quitbotton.qrc \
    tower.qrc \
    bullet.qrc \
    enemy.qrc \
    media.qrc

DISTFILES +=
