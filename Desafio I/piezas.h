#ifndef PIEZA_H
#define PIEZA_H

#include <cstdint> // corregi la cabecera 

const int MAX_FILAS_PIEZA = 4;
const int NUM_PIEZAS      = 6;

// cambie por class
class Pieza {
public:
    char    id;
    int     anchoBase;
    int     altoBase;
    uint8_t formaBase[MAX_FILAS_PIEZA];
};

class Forma {
public:
    int     ancho;
    int     alto;
    uint8_t filas[MAX_FILAS_PIEZA];
};

class PiezaActiva {
public:
    Pieza* tipo;
    int    rotActual;
    int    x;
    int    y;
};

// Prototipos de funciones
void inicializarPiezas(Pieza* piezas);
int obtenerBit(const Forma* f, int fila, int col);
Forma rotarForma(const Forma* f);
Forma obtenerFormaActual(const Pieza* pieza, int numRotaciones);
PiezaActiva generarNuevaPieza(Pieza* piezas, int anchoTablero);
void rotarPieza(PiezaActiva* pa);

#endif
