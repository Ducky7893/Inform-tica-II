#ifndef COLISIONES_H
#define COLISIONES_H

#include "tablero.h"
#include "piezas.h"


bool puedeColocarPieza(const Tablero* t, const PiezaActiva* pa);

void fijarPiezaEnTablero(Tablero* t, const PiezaActiva* pa);

int eliminarLineas(Tablero* t);

#endif
