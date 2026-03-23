# Desafio-I
Aquí se realizara el desafío I de informática II de la Universidad de Antioquia en el periodo 2026-01
Informe Preeliminar:
Tetris, Desafío I Pre informe.
Arquitectura y estructura de archivos 

Esta es nuestra propuesta para una primer version prematura de este proyecto, en donde se incluyen un archivo para la nucleo del juego, en donde se ingresaran los comandos que ejecutara el usuario y con en base a esto, invocara a otras funciones como nucleo de juego para realizar movimientos, en la consola se verificaran las jugadas, se invocaran funciones para actualizar tableros, se verificaran colisiones, game over y demas, el tablero contendrá toda la informacion del tablero, como el tamaño del mismo, tambien se actualizara no tan frecuentemente para mostrar el tablero en pantalla y etc.
VIDEO FINAL. 
https://youtu.be/eVqwPiTG0UA
```
/tetris-bitwise/
  |-- src/
       |-- main.cpp
       |-- Nucleojuego.cpp
       |-- Nucleojuego.h
       |-- tablero.cpp
       |-- tablero.h
       |-- piezas.cpp
       |-- piezas.h
       |-- io_consola.cpp
       |-- io_consola.h
       |-- utilidades.cpp
       |-- utilidades.h
  |-- reporte(informe)           
  |-- video/            
  |-- Makefile / .pro (Qt project)
  |-- PLAN.md
  |-- README.md
  ```
