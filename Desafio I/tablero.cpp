#include "tablero.h"
#include <iostream>

void inicializarTablero(Tablero* t, int ancho, int alto) {
    t->ancho        = ancho;
    t->alto         = alto;
    t->bytesPorFila = ancho / 8;

    int totalBytes = alto * t->bytesPorFila;
    t->memoria = new uint8_t[totalBytes];

   
    uint8_t* ptr = t->memoria;
    for (int i = 0; i < totalBytes; i++) {
        *(ptr + i) = 0;
    }
}

void liberarTablero(Tablero* t) {
    delete[] t->memoria;
    t->memoria = nullptr;
}

void imprimirTablero(const Tablero* t) {
    for (int fila = 0; fila < t->alto; fila++) {
        std::cout << '|';

        for (int b = 0; b < t->bytesPorFila; b++) {
            // Corregi: Aritmética de punteros en lugar de índices [] xd
            uint8_t byteActual = *(t->memoria + (fila * t->bytesPorFila) + b);

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
        // Corregi por : Aritmética de punteros
        if (*(t->memoria + (fila * t->bytesPorFila) + b) != 0xFF)
            return false;
    }
    return true;
}

void eliminarFila(Tablero* t, int fila) {
    
    for (int f = fila; f > 0; f--) {
        uint8_t* filaDestino = t->memoria + (f * t->bytesPorFila);
        uint8_t* filaOrigen = t->memoria + ((f - 1) * t->bytesPorFila);

        for (int b = 0; b < t->bytesPorFila; b++) {
            *(filaDestino + b) = *(filaOrigen + b);
        }
    }
    insertarFilaCero(t);
}

void insertarFilaCero(Tablero* t) {
  
    uint8_t* primeraFila = t->memoria;
    for (int b = 0; b < t->bytesPorFila; b++)
        *(primeraFila + b) = 0;
}
