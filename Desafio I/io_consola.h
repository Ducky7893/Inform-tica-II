#ifndef IO_CONSOLA_H
#define IO_CONSOLA_H

#include "tablero.h"
#include "piezas.h"

// Solicita al usuario las dimensiones del tablero con validacion
// Ancho: minimo 8, multiplo estricto de 8
// Alto:  minimo 8
void pedirDimensiones(int* ancho, int* alto);

// Solicita una accion al usuario y retorna el caracter ingresado
// Opciones validas: A (izq), D (der), S (bajar), W (rotar), Q (salir)
char pedirAccion();

// Imprime el tablero con la pieza activa superpuesta (sin modificar la memoria real)
void imprimirEstadoConsola(const Tablero* t, const PiezaActiva* pa, int puntaje);

// Imprime mensaje de Game Over con el puntaje final
void imprimirGameOver(int puntaje);

#endif
