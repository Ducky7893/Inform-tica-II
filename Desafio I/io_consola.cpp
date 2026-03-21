#include "io_consola.h"
#include <iostream>

void pedirDimensiones(int* ancho, int* alto) {
    // --- Pedir ANCHO ---
    do {
        std::cout << "Ingrese el ancho del tablero (minimo 8, multiplo de 8): ";
        std::cin >> *ancho;

        if (*ancho < 8) {
            std::cout << "Error: el ancho minimo es 8.\n";
        } else if (*ancho % 8 != 0) {
            std::cout << "Error: el ancho debe ser multiplo de 8.\n";
        }
    } while (*ancho < 8 || *ancho % 8 != 0);

    // --- Pedir ALTO ---
    do {
        std::cout << "Ingrese el alto del tablero (minimo 8): ";
        std::cin >> *alto;

        if (*alto < 8) {
            std::cout << "Error: el alto minimo es 8.\n";
        }
    } while (*alto < 8);
}

char pedirAccion() {
    char accion;
    std::cout << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
    std::cin >> accion;
    return accion;
}

void imprimirEstadoConsola(const Tablero* t, const PiezaActiva* pa, int puntaje) {
    int bytesPorFila = t->bytesPorFila;
    int alto         = t->alto;
    int ancho        = t->ancho;
    uint8_t* mem     = t->memoria;

    // Copia temporal del tablero para superponer la pieza activa
    int totalBytes = alto * bytesPorFila;
    uint8_t* copia = new uint8_t[totalBytes];

    for (int i = 0; i < totalBytes; i++) {
        *(copia + i) = *(mem + i);
    }

    // Superponer la pieza activa en la copia usando bitwise
    Forma forma = obtenerFormaActual(pa->tipo, pa->rotActual);

    for (int filaP = 0; filaP < forma.alto; filaP++) {
        int filaT = pa->y + filaP;
        if (filaT < 0 || filaT >= alto) continue;

        int bitOffset  = pa->x % 8;
        int byteOffset = pa->x / 8;
        uint8_t filaBits = *(forma.filas + filaP);

        // Byte principal
        if (byteOffset < bytesPorFila) {
            *(copia + filaT * bytesPorFila + byteOffset) |= (filaBits >> bitOffset);
        }

        // Byte siguiente si la pieza cruza la frontera de byte
        if (bitOffset > 0 && (byteOffset + 1) < bytesPorFila) {
            *(copia + filaT * bytesPorFila + byteOffset + 1) |= (uint8_t)(filaBits << (8 - bitOffset));
        }
    }

    // Imprimir puntaje
    std::cout << "\nPuntaje: " << puntaje << "\n";

    // Imprimir tablero con '#' y '.'
    for (int fila = 0; fila < alto; fila++) {
        std::cout << '|';
        for (int b = 0; b < bytesPorFila; b++) {
            uint8_t byteActual = *(copia + fila * bytesPorFila + b);
            for (int bit = 7; bit >= 0; bit--) {
                uint8_t mascara = (uint8_t)(1 << bit);
                std::cout << ((byteActual & mascara) ? '#' : '.');
            }
        }
        std::cout << "|\n";
    }

    // Borde inferior
    std::cout << '+';
    for (int c = 0; c < ancho; c++) std::cout << '-';
    std::cout << "+\n";

    delete[] copia;
}

void imprimirGameOver(int puntaje) {
    std::cout << "\n=== GAME OVER ===\n";
    std::cout << "Puntaje final: " << puntaje << "\n";
}
