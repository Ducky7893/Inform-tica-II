#ifndef TABLERO_H
#define TABLERO_H
#include <stdint.h>

struct Tablero {
    uint8_t* memoria;
    int ancho;
    int alto;
    int bytesPorFila;
};

void inicializarTablero(Tablero* t, int ancho, int alto);
void liberarTablero(Tablero* t);
void imprimirTablero(const Tablero* t);
bool filaCompleta(const Tablero* t, int fila);
void eliminarFila(Tablero* t, int fila);
void insertarFilaCero(Tablero* t);

#endif
