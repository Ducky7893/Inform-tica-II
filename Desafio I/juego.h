#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "piezas.h"

class Juego {
public:
    Tablero     tablero;            
    void inicializar(int ancho, int alto);
    void liberar();
    void cicloDelJuego();

private:
    Pieza       piezas[NUM_PIEZAS]; 
    PiezaActiva piezaActiva;        
    int         puntaje;            
    bool        gameOver;          

    void procesarAccion(char accion);
    void moverIzquierda();
    void moverDerecha();
    void moverAbajo();
    void rotar();
    void spawnNuevaPieza();

};
#endif // JUEGO_H