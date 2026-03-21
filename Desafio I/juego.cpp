#include "juego.h"
#include "io_consola.h" 

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
        
        imprimirEstadoConsola(&tablero, &piezaActiva, puntaje);
        char accion = pedirAccion();
        procesarAccion(accion);
    }
    imprimirGameOver(puntaje);
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
    if (puedeColocar(&temp)) piezaActiva = temp;
}

void Juego::moverDerecha() {
    PiezaActiva temp = piezaActiva;
    temp.x += 1;
    if (puedeColocar(&temp)) piezaActiva = temp;
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
    if (puedeColocar(&temp)) piezaActiva = temp;
}

bool Juego::puedeColocar(const PiezaActiva* pa) const {
    Forma forma = obtenerFormaActual(pa->tipo, pa->rotActual);

    int bytesPorFila = tablero.bytesPorFila;
    int alto         = tablero.alto;
    int ancho        = tablero.ancho;
    uint8_t* mem     = tablero.memoria;

    // Buffer dinamico segun el ancho real del tablero 
    uint8_t* bufferFila = new uint8_t[bytesPorFila];

    bool colision = false;

    for (int filaP = 0; filaP < forma.alto; filaP++) {
        int filaT = pa->y + filaP;

        if (filaT >= alto) { colision = true; break; }
        if (filaT < 0) continue;
        if (pa->x < 0 || pa->x + forma.ancho > ancho) { colision = true; break; }

        // Limpiar buffer con aritmetica de punteros
        for (int b = 0; b < bytesPorFila; b++) *(bufferFila + b) = 0;

        int bitOffset  = pa->x % 8;
        int byteOffset = pa->x / 8;

    
        uint8_t filaBits = *(forma.filas + filaP);

        if (byteOffset < bytesPorFila) {
            *(bufferFila + byteOffset) |= (filaBits >> bitOffset);
        }
        if (bitOffset > 0 && (byteOffset + 1) < bytesPorFila) {
            *(bufferFila + byteOffset + 1) |= (uint8_t)(filaBits << (8 - bitOffset));
        }

        // Comparacion bit a bit con el tablero real
        for (int b = 0; b < bytesPorFila; b++) {
            if (*(bufferFila + b) & *(mem + filaT * bytesPorFila + b)) {
                colision = true;
                break;
            }
        }
        if (colision) break;
    }

    delete[] bufferFila;
    return !colision;
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

       
        uint8_t filaBits = *(forma.filas + filaP);

        *(mem + filaT * bytesPorFila + byteOffset) |= (filaBits >> bitOffset);

        if (bitOffset > 0 && byteOffset + 1 < bytesPorFila) {
            *(mem + filaT * bytesPorFila + byteOffset + 1) |= (uint8_t)(filaBits << (8 - bitOffset));
        }
    }
}

void Juego::eliminarLineas() {
    int fila = tablero.alto - 1;
    while (fila >= 0) {
        if (filaCompleta(&tablero, fila)) {
            eliminarFila(&tablero, fila);
            puntaje += 100;
            // No decrementar fila: la que bajo debe re-evaluarse
        } else {
            fila--;
        }
    }
}

void Juego::spawnNuevaPieza() {
    piezaActiva = generarNuevaPieza(piezas, tablero.ancho);
}
