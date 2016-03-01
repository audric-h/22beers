TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    business/position.cpp \
    business/board.cpp \
    business/player.cpp \
    business/wall.cpp \
    business/case.cpp \
    business/game.cpp \
    view/display.cpp

HEADERS += \
    business/direction.h \
    business/orientation.h \
    business/position.h \
    business/board.h \
    business/player.h \
    business/wall.h \
    business/case.h \
    business/game.h \
    keyboardAndStringConvert/keyboard.hpp \
    view/display.h
