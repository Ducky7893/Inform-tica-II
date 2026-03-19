#ifndef PIEZAS_H
#define PIEZAS_H

#include <stdint.h>

const int MAX_FILAS_PIEZA = 4;
const int NUM_PIEZAS      = 6;

struct Pieza {
    char    id;
    int     anchoBase;
    int     altoBase;
    uint8_t formaBase[MAX_FILAS_PIEZA];
};

struct Forma {
    int     ancho;
    int     alto;
    uint8_t filas[MAX_FILAS_PIEZA];
};

struct PiezaActiva {
    Pieza* tipo;
    int    rotActual;
    int    x;
    int    y;
};

void inicializarPiezas(Pieza* piezas);

int obtenerBit(const Forma* f, int fila, int col);

Forma rotarForma(const Forma* f);

Forma obtenerFormaActual(const Pieza* pieza, int numRotaciones);

PiezaActiva generarNuevaPieza(Pieza* piezas, int anchoTablero);

void rotarPieza(PiezaActiva* pa);

#endif
