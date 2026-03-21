#include "piezas.h"
#include <cstdlib>  // rand() — Única librería externa autorizada según tu indicación

void inicializarPiezas(Pieza* piezas) {
    // Usamos aritmética de punteros para acceder a los elementos del arreglo de piezas

    // PIEZA I — Línea horizontal
    Pieza* pI = (piezas + 0);
    pI->id         = 'I';
    pI->anchoBase  = 4;
    pI->altoBase   = 1;
    *(pI->formaBase + 0) = 0xF0; // 11110000

    // PIEZA O — Cuadrado 2x2
    Pieza* pO = (piezas + 1);
    pO->id         = 'O';
    pO->anchoBase  = 2;
    pO->altoBase   = 2;
    *(pO->formaBase + 0) = 0xC0; // 11000000
    *(pO->formaBase + 1) = 0xC0;

    // PIEZA T
    Pieza* pT = (piezas + 2);
    pT->id         = 'T';
    pT->anchoBase  = 3;
    pT->altoBase   = 2;
    *(pT->formaBase + 0) = 0x40; // 01000000
    *(pT->formaBase + 1) = 0xE0; // 11100000

    // PIEZA S
    Pieza* pS = (piezas + 3);
    pS->id         = 'S';
    pS->anchoBase  = 3;
    pS->altoBase   = 2;
    *(pS->formaBase + 0) = 0x60; // 01100000
    *(pS->formaBase + 1) = 0xC0; // 11000000

    // PIEZA Z
    Pieza* pZ = (piezas + 4);
    pZ->id         = 'Z';
    pZ->anchoBase  = 3;
    pZ->altoBase   = 2;
    *(pZ->formaBase + 0) = 0xC0;
    *(pZ->formaBase + 1) = 0x60;

    // PIEZA J
    Pieza* pJ = (piezas + 5);
    pJ->id         = 'J';
    pJ->anchoBase  = 3;
    pJ->altoBase   = 2;
    *(pJ->formaBase + 0) = 0x80; // 10000000
    *(pJ->formaBase + 1) = 0xE0; // 11100000
}

int obtenerBit(const Forma* f, int fila, int col) {
    // Uso de bitwise y aritmética de punteros
    uint8_t filaByte = *(f->filas + fila);
    return (filaByte >> (7 - col)) & 1;
}

Forma rotarForma(const Forma* f) {
    Forma resultado;
    resultado.ancho = f->alto;
    resultado.alto  = f->ancho;

    // Limpiar filas del resultado usando punteros
    for (int i = 0; i < MAX_FILAS_PIEZA; i++) {
        *(resultado.filas + i) = 0;
    }

    for (int fila = 0; fila < f->alto; fila++) {
        for (int col = 0; col < f->ancho; col++) {
            if (obtenerBit(f, fila, col) == 1) {
                int nuevaFila = col;
                int nuevoCol  = f->alto - 1 - fila;
                // Aplicar máscara de bits con OR
                *(resultado.filas + nuevaFila) |= (uint8_t)(1 << (7 - nuevoCol));
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
        *(forma.filas + i) = (i < pieza->altoBase) ? *(pieza->formaBase + i) : 0;
    }

    // El número de rotaciones efectivas es mod 4
    int rotaciones = numRotaciones % 4;
    for (int r = 0; r < rotaciones; r++) {
        forma = rotarForma(&forma);
    }

    return forma;
}

PiezaActiva generarNuevaPieza(Pieza* piezas, int anchoTablero) {
    int indice = rand() % NUM_PIEZAS;

    PiezaActiva pa;
    pa.tipo      = (piezas + indice);
    pa.rotActual = 0;
    // Centrar pieza: aritmética simple
    pa.x = (anchoTablero - pa.tipo->anchoBase) / 2;
    pa.y = 0;

    return pa;
}

void rotarPieza(PiezaActiva* pa) {
    // Operador módulo para mantener la rotación entre 0 y 3
    pa->rotActual = (pa->rotActual + 1) % 4;
}
