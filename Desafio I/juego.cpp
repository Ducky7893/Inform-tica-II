#include "juego.h"
#include <iostream>

void Juego::inicializar(int ancho, int alto) {
    inicializarTablero(&tablero, ancho, alto);
    inicializarPiezas(piezas);
    puntaje  = 0;
    gameOver = false;
    spawnNuevaPieza();
}

void Juego::liberar() {
    liberarTablero(&tablero);
}

void Juego::cicloDelJuego() {
    while (!gameOver) {
        imprimirEstado();
        std::cout << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";

        char accion;
        std::cin >> accion;

        procesarAccion(accion);
    }

    std::cout << "\n=== GAME OVER ===\n";
    std::cout << "Puntaje final: " << puntaje << "\n";
}

void Juego::procesarAccion(char accion) {
    if      (accion == 'A' || accion == 'a') moverIzquierda();
    else if (accion == 'D' || accion == 'd') moverDerecha();
    else if (accion == 'S' || accion == 's') moverAbajo();
    else if (accion == 'W' || accion == 'w') rotar();
    else if (accion == 'Q' || accion == 'q') gameOver = true;
}

void Juego::moverIzquierda() {
    PiezaActiva temp = piezaActiva;
    temp.x -= 1;
    if (puedeColocar(&temp)) {
        piezaActiva = temp;
    }
}

void Juego::moverDerecha() {
    PiezaActiva temp = piezaActiva;
    temp.x += 1;
    if (puedeColocar(&temp)) {
        piezaActiva = temp;
    }
}

void Juego::moverAbajo() {
    PiezaActiva temp = piezaActiva;
    temp.y += 1;

    if (puedeColocar(&temp)) {
        piezaActiva = temp;
    } else {
        fijarPieza();
        eliminarLineas();
        spawnNuevaPieza();

        if (!puedeColocar(&piezaActiva)) {
            gameOver = true;
        }
    }
}

void Juego::rotar() {
    PiezaActiva temp = piezaActiva;
    rotarPieza(&temp);
    if (puedeColocar(&temp)) {
        piezaActiva = temp;
    }
}

bool Juego::puedeColocar(const PiezaActiva* pa) const {
    Forma forma = obtenerFormaActual(pa->tipo, pa->rotActual);

    int bytesPorFila = tablero.bytesPorFila;
    int alto         = tablero.alto;
    int ancho        = tablero.ancho;
    uint8_t* mem     = tablero.memoria;

    for (int filaP = 0; filaP < forma.alto; filaP++) {
        int filaT = pa->y + filaP;

        // Verificar que no se salga por el piso
        if (filaT >= alto) return false;

        // Filas por encima del tablero son validas (pieza apareciendo)
        if (filaT < 0) continue;

        // Verificar bordes horizontales
        if (pa->x < 0)                   return false;
        if (pa->x + forma.ancho > ancho) return false;

        int bitOffset  = pa->x % 8;
        int byteOffset = pa->x / 8;

        uint8_t filaBits = forma.filas[filaP];

        uint8_t temp[4] = {0, 0, 0, 0};

        *(temp + byteOffset) |= (filaBits >> bitOffset);

        if (bitOffset > 0 && byteOffset + 1 < bytesPorFila) {
            *(temp + byteOffset + 1) |= (filaBits << (8 - bitOffset));
        }

        for (int b = 0; b < bytesPorFila; b++) {
            if (*(temp + b) & *(mem + filaT * bytesPorFila + b)) {
                return false;  // colision detectada
            }
        }
    }

    return true;
}

void Juego::fijarPieza() {
    Forma forma = obtenerFormaActual(piezaActiva.tipo, piezaActiva.rotActual);

    int bytesPorFila = tablero.bytesPorFila;
    uint8_t* mem     = tablero.memoria;

    for (int filaP = 0; filaP < forma.alto; filaP++) {
        int filaT = piezaActiva.y + filaP;
        if (filaT < 0 || filaT >= tablero.alto) continue;

        int bitOffset  = piezaActiva.x % 8;
        int byteOffset = piezaActiva.x / 8;

        uint8_t filaBits = forma.filas[filaP];

        *(mem + filaT * bytesPorFila + byteOffset) |= (filaBits >> bitOffset);

        if (bitOffset > 0 && byteOffset + 1 < bytesPorFila) {
            *(mem + filaT * bytesPorFila + byteOffset + 1) |= (filaBits << (8 - bitOffset));
        }
    }
}

void Juego::eliminarLineas() {
    int fila = tablero.alto - 1;

    while (fila >= 0) {
        if (filaCompleta(&tablero, fila)) {
            eliminarFila(&tablero, fila);
            puntaje += 100;
        } else {
            fila--;
        }
    }
}

void Juego::spawnNuevaPieza() {
    piezaActiva = generarNuevaPieza(piezas, tablero.ancho);
}

void Juego::imprimirEstado() const {
    int bytesPorFila = tablero.bytesPorFila;
    int alto         = tablero.alto;
    int ancho        = tablero.ancho;
    uint8_t* mem     = tablero.memoria;

    int totalBytes   = alto * bytesPorFila;
    uint8_t* copia   = new uint8_t[totalBytes];

    for (int i = 0; i < totalBytes; i++) {
        *(copia + i) = *(mem + i);
    }

    Forma forma = obtenerFormaActual(piezaActiva.tipo, piezaActiva.rotActual);

    for (int filaP = 0; filaP < forma.alto; filaP++) {
        int filaT = piezaActiva.y + filaP;
        if (filaT < 0 || filaT >= alto) continue;

        int bitOffset  = piezaActiva.x % 8;
        int byteOffset = piezaActiva.x / 8;
        uint8_t filaBits = forma.filas[filaP];

        *(copia + filaT * bytesPorFila + byteOffset) |= (filaBits >> bitOffset);
        if (bitOffset > 0 && byteOffset + 1 < bytesPorFila) {
            *(copia + filaT * bytesPorFila + byteOffset + 1) |= (filaBits << (8 - bitOffset));
        }
    }
    std::cout << "\nPuntaje: " << puntaje << "\n";
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
    std::cout << '+';
    for (int c = 0; c < ancho; c++) std::cout << '-';
    std::cout << "+\n";

    delete[] copia;
}