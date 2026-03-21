#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "piezas.h"

class Juego {
public:
    void inicializar(int ancho, int alto);
    void liberar();
    void cicloDelJuego();

private:
    Tablero     tablero;
    Pieza       piezas[NUM_PIEZAS];
    PiezaActiva piezaActiva;
    int         puntaje;
    bool        gameOver;

    void procesarAccion(char accion);
    void moverIzquierda();
    void moverDerecha();
    void moverAbajo();
    void rotar();

    bool puedeColocar(const PiezaActiva* pa) const;
    void fijarPieza();
    void eliminarLineas();
    void spawnNuevaPieza();
    // imprimirEstado() eliminada — ahora usa imprimirEstadoConsola() de io_consola
};

#endif // JUEGO_H
