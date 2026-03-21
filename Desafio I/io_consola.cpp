#include "io_consola.h"
#include "tablero.h"
#include "piezas.h"
#include <cstdint>
#include <iostream>
#include <limits>

void pedirDimensiones(int* ancho, int* alto) {
    // --- Pedir ANCHO ---
    do {
        std::cout << "Ingrese el ancho del tablero (minimo 8, multiplo de 8): ";

        if (!(std::cin >> *ancho)) {
            // Limpiar el estado de error y el buffer si el usuario ingresa texto
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            *ancho = 0;
            std::cout << "Error: ingrese un numero valido.\n";
            continue;
        }

        if (*ancho < 8) {
            std::cout << "Error: el ancho minimo es 8.\n";
        } else if (*ancho % 8 != 0) {
            std::cout << "Error: el ancho debe ser multiplo de 8 (ej: 8, 16, 24).\n";
        }
    } while (*ancho < 8 || *ancho % 8 != 0);

    // --- Pedir ALTO ---
    do {
        std::cout << "Ingrese el alto del tablero (minimo 8): ";

        if (!(std::cin >> *alto)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            *alto = 0;
            std::cout << "Error: ingrese un numero valido.\n";
            continue;
        }

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

    int totalBytes = alto * bytesPorFila;
    uint8_t* copia = new uint8_t[totalBytes];

    for (int i = 0; i < totalBytes; i++) {
        *(copia + i) = *(mem + i);
    }

    Forma forma = obtenerFormaActual(pa->tipo, pa->rotActual);

    for (int filaP = 0; filaP < forma.alto; filaP++) {
        int filaT = pa->y + filaP;
        if (filaT < 0 || filaT >= alto) continue;

        int bitOffset  = pa->x % 8;
        int byteOffset = pa->x / 8;
        uint8_t filaBits = *(forma.filas + filaP);

        int idxPrincipal = filaT * bytesPorFila + byteOffset;
        if (byteOffset >= 0 && byteOffset < bytesPorFila
            && idxPrincipal >= 0 && idxPrincipal < totalBytes) {
            *(copia + idxPrincipal) |= (filaBits >> bitOffset);
        }

        int idxSiguiente = filaT * bytesPorFila + byteOffset + 1;
        if (bitOffset > 0 && (byteOffset + 1) < bytesPorFila
            && idxSiguiente >= 0 && idxSiguiente < totalBytes) {
            *(copia + idxSiguiente) |= (uint8_t)(filaBits << (8 - bitOffset));
        }
    }

    std::cout << "\nPuntaje: " << puntaje << "\n";

    for (int fila = 0; fila < alto; fila++) {
        std::cout << '|';
        for (int b = 0; b < bytesPorFila; b++) {
            int idx = fila * bytesPorFila + b;
            uint8_t byteActual = (idx >= 0 && idx < totalBytes) ? *(copia + idx) : 0;
            for (int bit = 7; bit >= 0; bit--) {
                uint8_t mascara = (uint8_t)(1 << bit);
                std::cout << ((byteActual & mascara) ? '#' : '.');
            }
        }
        std::cout << "|\n";
    }

    std::cout << '+';
    for (int c = 0; c < ancho; c++) std::cout << '-';
    std::cout << "+\n";

    delete[] copia;
}

void imprimirGameOver(int puntaje) {
    std::cout << "\n===================\n";
    std::cout << "    GAME OVER      \n";
    std::cout << " Puntaje final: " << puntaje << "\n";
    std::cout << "===================\n";
}
