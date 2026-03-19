#include "piezas.h"
#include <cstdlib>  // rand() — unica libreria externa autorizada

void inicializarPiezas(Pieza* piezas) {
    // PIEZA I — linea horizontal de 4 bloques
    //   ####
    piezas[0].id         = 'I';
    piezas[0].anchoBase  = 4;
    piezas[0].altoBase   = 1;
    piezas[0].formaBase[0] = 0xF0;

    // PIEZA O — cuadrado 2x2
    //   ##
    //   ##
    piezas[1].id         = 'O';
    piezas[1].anchoBase  = 2;
    piezas[1].altoBase   = 2;
    piezas[1].formaBase[0] = 0xC0;
    piezas[1].formaBase[1] = 0xC0;

    // PIEZA T
    //   .#.
    //   ###
    piezas[2].id         = 'T';
    piezas[2].anchoBase  = 3;
    piezas[2].altoBase   = 2;
    piezas[2].formaBase[0] = 0x40;
    piezas[2].formaBase[1] = 0xE0;

    // PIEZA S
    //   .##
    //   ##.
    piezas[3].id         = 'S';
    piezas[3].anchoBase  = 3;
    piezas[3].altoBase   = 2;
    piezas[3].formaBase[0] = 0x60;
    piezas[3].formaBase[1] = 0xC0;

    // PIEZA Z
    //   ##.
    //   .##
    piezas[4].id         = 'Z';
    piezas[4].anchoBase  = 3;
    piezas[4].altoBase   = 2;
    piezas[4].formaBase[0] = 0xC0;
    piezas[4].formaBase[1] = 0x60;

    // PIEZA J  gancho a la izquierda
    //   #..
    //   ###
    piezas[5].id         = 'J';
    piezas[5].anchoBase  = 3;
    piezas[5].altoBase   = 2;
    piezas[5].formaBase[0] = 0x80;
    piezas[5].formaBase[1] = 0xE0;
}


int obtenerBit(const Forma* f, int fila, int col) {
    return (f->filas[fila] >> (7 - col)) & 1;
}

Forma rotarForma(const Forma* f) {
    Forma resultado;
    resultado.ancho = f->alto;
    resultado.alto  = f->ancho;

    for (int i = 0; i < MAX_FILAS_PIEZA; i++) {
        resultado.filas[i] = 0;
    }
    for (int fila = 0; fila < f->alto; fila++) {
        for (int col = 0; col < f->ancho; col++) {

            int bit = obtenerBit(f, fila, col);

            if (bit == 1) {

                int nuevaFila = col;
                int nuevoCol  = f->alto - 1 - fila;

                resultado.filas[nuevaFila] |= (uint8_t)(1 << (7 - nuevoCol));
            }
        }
    }
    return resultado;
}

Forma obtenerFormaActual(const Pieza* pieza, int numRotaciones) {

    Forma forma;
    forma.ancho = pieza->anchoBase;
    forma.alto  = pieza->altoBase;

    for (int i = 0; i < MAX_FILAS_PIEZA; i++) {
        forma.filas[i] = 0;
    }
    for (int i = 0; i < pieza->altoBase; i++) {
        forma.filas[i] = pieza->formaBase[i];
    }
    for (int r = 0; r < numRotaciones; r++) {
        forma = rotarForma(&forma);
    }

    return forma;
}

PiezaActiva generarNuevaPieza(Pieza* piezas, int anchoTablero) {
    int indice = rand() % NUM_PIEZAS;

    PiezaActiva pa;
    pa.tipo      = &piezas[indice];
    pa.rotActual = 0;

    pa.x = (anchoTablero - pa.tipo->anchoBase) / 2;
    pa.y = 0;

    return pa;
}
void rotarPieza(PiezaActiva* pa) {
    pa->rotActual = (pa->rotActual + 1) % 4;
}
