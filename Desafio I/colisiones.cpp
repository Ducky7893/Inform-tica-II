#include "colisiones.h"
#include <cstdint>

static void alinearFilaPieza(uint8_t* buffer, uint8_t filaPieza, int x, int bytesPorFila) {
    // Subimos a 16 bits para poder desplazar sin perder bits al cruzar el limite de byte
    uint16_t bits = (uint16_t)filaPieza << 8;
    bits = bits >> x;
    int byteOffset = x / 8;

    // Validacion explicita de indices para el analizador estatico
    if (byteOffset >= 0 && byteOffset < bytesPorFila)
        *(buffer + byteOffset) |= (uint8_t)(bits >> 8);

    if ((byteOffset + 1) >= 0 && (byteOffset + 1) < bytesPorFila)
        *(buffer + byteOffset + 1) |= (uint8_t)(bits & 0xFF);
}

bool puedeColocarPieza(const Tablero* t, const PiezaActiva* pa) {
    Forma f = obtenerFormaActual(pa->tipo, pa->rotActual);
    uint8_t* filaBuffer = new uint8_t[t->bytesPorFila];
    bool colision = false;

    for (int i = 0; i < f.alto; i++) {
        int filaTablero = pa->y + i;
        for (int b = 0; b < t->bytesPorFila; b++) *(filaBuffer + b) = 0;

        if (filaTablero < 0 || filaTablero >= t->alto) {
            if (*(f.filas + i) != 0) { colision = true; break; }
            continue;
        }
        if (pa->x < 0 || (pa->x + f.ancho) > t->ancho) { colision = true; break; }

        alinearFilaPieza(filaBuffer, *(f.filas + i), pa->x, t->bytesPorFila);

        for (int b = 0; b < t->bytesPorFila; b++) {
            if (*(filaBuffer + b) & *(t->memoria + (filaTablero * t->bytesPorFila) + b)) {
                colision = true; break;
            }
        }
        if (colision) break;
    }

    delete[] filaBuffer;
    return !colision;
}

void fijarPiezaEnTablero(Tablero* t, const PiezaActiva* pa) {
    Forma f = obtenerFormaActual(pa->tipo, pa->rotActual);
    uint8_t* filaBuffer = new uint8_t[t->bytesPorFila];

    for (int i = 0; i < f.alto; i++) {
        int filaTablero = pa->y + i;
        if (filaTablero < 0 || filaTablero >= t->alto) continue;
        for (int b = 0; b < t->bytesPorFila; b++) *(filaBuffer + b) = 0;
        alinearFilaPieza(filaBuffer, *(f.filas + i), pa->x, t->bytesPorFila);
        for (int b = 0; b < t->bytesPorFila; b++)
            *(t->memoria + (filaTablero * t->bytesPorFila) + b) |= *(filaBuffer + b);
    }

    delete[] filaBuffer;
}

int eliminarLineas(Tablero* t) {
    int contador = 0;
    for (int f = t->alto - 1; f >= 0; f--) {
        if (filaCompleta(t, f)) {
            eliminarFila(t, f);
            contador++;
            f++; // Re-evaluar la misma posicion ya que lo de arriba bajo
        }
    }
    return contador;
}
