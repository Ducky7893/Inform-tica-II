#include "juego.h"
#include "io_consola.h"

void Juego::inicializar(int ancho, int alto) {
    inicializarTablero(&tablero, ancho, alto);
    inicializarPiezas(piezas);
    puntaje  = 0;
    gameOver = false;
    spawnNuevaPieza();
}

void Juego::liberar() {
    liberarTablero(&tablero);
}

void Juego::cicloDelJuego() {
    while (!gameOver) {
        imprimirEstadoConsola(&tablero, &piezaActiva, puntaje);
        char accion = pedirAccion();
        procesarAccion(accion);
    }
    imprimirGameOver(puntaje);
}

void Juego::procesarAccion(char accion) {
    if      (accion == 'A' || accion == 'a') moverIzquierda();
    else if (accion == 'D' || accion == 'd') moverDerecha();
    else if (accion == 'S' || accion == 's') moverAbajo();
    else if (accion == 'W' || accion == 'w') rotar();
    else if (accion == 'Q' || accion == 'q') gameOver = true;
}

void Juego::moverIzquierda() {
    PiezaActiva temp = piezaActiva;
    temp.x -= 1;
    if (puedeColocarPieza(&tablero, &temp)) piezaActiva = temp;
}

void Juego::moverDerecha() {
    PiezaActiva temp = piezaActiva;
    temp.x += 1;
    if (puedeColocarPieza(&tablero, &temp)) piezaActiva = temp;
}

void Juego::moverAbajo() {
    PiezaActiva temp = piezaActiva;
    temp.y += 1;

    if (puedeColocarPieza(&tablero, &temp)) {
        piezaActiva = temp;
    } else {
        fijarPiezaEnTablero(&tablero, &piezaActiva);
        int lineas = eliminarLineas(&tablero);
        puntaje += lineas * 100;
        spawnNuevaPieza();

        if (!puedeColocarPieza(&tablero, &piezaActiva)) {
            gameOver = true;
        }
    }
}

void Juego::rotar() {
    PiezaActiva temp = piezaActiva;
    rotarPieza(&temp);
    if (puedeColocarPieza(&tablero, &temp)) piezaActiva = temp;
}

void Juego::spawnNuevaPieza() {
    piezaActiva = generarNuevaPieza(piezas, tablero.ancho);
}