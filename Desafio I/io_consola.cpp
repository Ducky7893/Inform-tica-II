#include "io_consola.h"
#include <iostream>

void pedirDimensiones(int* ancho, int* alto) {
    // Validación de Ancho (Mínimo 8 y múltiplo de 8 por gestión de bytes)
    do {
        std::cout << "Ingrese el ancho del tablero (minimo 8, multiplo de 8): ";
        std::cin >> *ancho;
        if (*ancho < 8 || *ancho % 8 != 0) {
            std::cout << "Error: El ancho debe ser minimo 8 y multiplo de 8.\n";
        }
    } while (*ancho < 8 || *ancho % 8 != 0);

    // Validación de Alto
    do {
        std::cout << "Ingrese el alto del tablero (minimo 8): ";
        std::cin >> *alto;
        if (*alto < 8) std::cout << "Error: El alto minimo es 8.\n";
    } while (*alto < 8);
}

char pedirAccion() {
    char accion;
    std::cout << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
    std::cin >> accion;
    return accion;
}

void imprimirEstadoConsola(const Tablero* t, const PiezaActiva* pa, int puntaje) {
    int totalBytes = t->alto * t->bytesPorFila;
    uint8_t* copia = new uint8_t[totalBytes];

    // Clonación del tablero real usando aritmética de punteros (Requisito 35%)
    for (int i = 0; i < totalBytes; i++) {
        *(copia + i) = *(t->memoria + i);
    }

    // Superposición de la pieza activa mediante operadores Bitwise
    Forma forma = obtenerFormaActual(pa->tipo, pa->rotActual);

    for (int filaP = 0; filaP < forma.alto; filaP++) {
        int filaT = pa->y + filaP;
        if (filaT < 0 || filaT >= t->alto) continue;

        int bitOffset  = pa->x % 8;
        int byteOffset = pa->x / 8;
        uint8_t filaBits = *(forma.filas + filaP);

        // Renderizado en byte principal y desborde (Bitwise)
        if (byteOffset < t->bytesPorFila) {
            *(copia + (filaT * t->bytesPorFila) + byteOffset) |= (filaBits >> bitOffset);
        }
        if (bitOffset > 0 && (byteOffset + 1) < t->bytesPorFila) {
            *(copia + (filaT * t->bytesPorFila) + byteOffset + 1) |= (uint8_t)(filaBits << (8 - bitOffset));
        }
    }

    std::cout << "\nPuntaje: " << puntaje << "\n";

    // Representación visual en consola
    for (int fila = 0; fila < t->alto; fila++) {
        std::cout << '|';
        for (int b = 0; b < t->bytesPorFila; b++) {
            uint8_t byteActual = *(copia + (fila * t->bytesPorFila) + b);
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

    delete[] copia; // Liberación de memoria dinámica
}

void imprimirGameOver(int puntaje) {
    std::cout << "\n===================\n";
    std::cout << "    GAME OVER      \n";
    std::cout << " Puntaje final: " << puntaje << "\n";
    std::cout << "===================\n";
}
