#include "tablero.h"
#include <iostream>

void inicializarTablero(Tablero* t, int ancho, int alto) {
    t->ancho        = ancho;
    t->alto         = alto;
    t->bytesPorFila = ancho / 8;

    int totalBytes = alto * t->bytesPorFila;
    t->memoria = new uint8_t[totalBytes];

    for (int i = 0; i < totalBytes; i++)
        t->memoria[i] = 0;
}

void liberarTablero(Tablero* t) {
    delete[] t->memoria;
    t->memoria = nullptr;
}

void imprimirTablero(const Tablero* t) {
    for (int fila = 0; fila < t->alto; fila++) {
        std::cout << '|';

        for (int b = 0; b < t->bytesPorFila; b++) {
            uint8_t byteActual = t->memoria[fila * t->bytesPorFila + b];

            for (int bit = 7; bit >= 0; bit--) {
                uint8_t mascara = (uint8_t)(1 << bit);
                std::cout << ((byteActual & mascara) ? '#' : '.');
            }
        }

        std::cout << "|\n";
    }

    std::cout << '+';
    for (int c = 0; c < t->ancho; c++) std::cout << '-';
    std::cout << "+\n";
}

bool filaCompleta(const Tablero* t, int fila) {
    for (int b = 0; b < t->bytesPorFila; b++) {
        // 0xFF = todos los bits en 1; si algún byte falla, la fila no está llena
        if (t->memoria[fila * t->bytesPorFila + b] != 0xFF)
            return false;
    }
    return true;
}

void eliminarFila(Tablero* t, int fila) {
    // Desplazar filas superiores una posición hacia abajo
    for (int f = fila; f > 0; f--) {
        for (int b = 0; b < t->bytesPorFila; b++) {
            t->memoria[f * t->bytesPorFila + b] =
                t->memoria[(f - 1) * t->bytesPorFila + b];
        }
    }
    insertarFilaCero(t);
}

void insertarFilaCero(Tablero* t) {
    for (int b = 0; b < t->bytesPorFila; b++)
        t->memoria[b] = 0;
}
