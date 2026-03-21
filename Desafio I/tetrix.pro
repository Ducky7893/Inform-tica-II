TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        colisiones.cpp \
        io_consola.cpp \
        juego.cpp \
        main.cpp \
        piezas.cpp \
        tablero.cpp

HEADERS += \
    colisiones.h \
    io_consola.h \
    juego.h \
    piezas.h \
    tablero.h
