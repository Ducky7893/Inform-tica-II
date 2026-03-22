#include "juego.h"
#include "io_consola.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand((unsigned int)time(nullptr));  // semilla aleatoria
    
    int ancho, alto;
    pedirDimensiones(&ancho, &alto);
    
    Juego juego;
    juego.inicializar(ancho, alto);

    std::cout << "Tablero inicial:\n";
    imprimirTablero(&juego.tablero); 

    juego.cicloDelJuego();
    juego.liberar();
    
    return 0;
}