#ifndef IO_CONSOLA_H
#define IO_CONSOLA_H

#include "tablero.h"
#include "piezas.h"

// Entrada de dimensiones con validación (Ancho múltiplo de 8, Alto min 8)
void pedirDimensiones(int* ancho, int* alto);

// Captura de entrada del usuario para control de piezas
char pedirAccion();

// Renderizado de tablero y pieza activa mediante buffer temporal (Bitwise)
void imprimirEstadoConsola(const Tablero* t, const PiezaActiva* pa, int puntaje);

// Notificación de fin de juego y estadísticas finales
void imprimirGameOver(int puntaje);

#endif
