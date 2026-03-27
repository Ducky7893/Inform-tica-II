#include <iostream>
#include <cstring>
#include "utilidades.h"

using namespace std;

void intToString(int num, char *&resultado) {
    int temp = num, len = 0;

    if (num == 0) {
        resultado = new char[2];
        resultado[0] = '0';
        resultado[1] = '\0';
        return;
    }

    if (num < 0) {
        temp = -temp;
        len++;
    }

    int t = temp;
    while (t > 0) {
        t /= 10;
        len++;
    }

    resultado = new char[len + 1];
    resultado[len] = '\0';

    int i = len - 1;
    while (temp > 0) {
        resultado[i--] = (temp % 10) + '0';
        temp /= 10;
    }

    if (num < 0) {
        resultado[0] = '-';
    }
}

void ejercicio_cinco() {
    int numero;
    char *cadena = nullptr;

    cout << "Ingrese un numero: ";
    cin >> numero;

    intToString(numero, cadena);

    cout << "Cadena: " << cadena << endl;

    delete[] cadena;
}

void eliminarRepetidos(char *entrada, char *&salida) {
    int n = strlen(entrada);

    salida = new char[n + 1];
    int k = 0;

    for (int i = 0; i < n; i++) {
        bool repetido = false;

        for (int j = 0; j < k; j++) {
            if (entrada[i] == salida[j]) {
                repetido = true;
                break;
            }
        }

        if (!repetido) {
            salida[k++] = entrada[i];
        }
    }

    salida[k] = '\0';
}

void ejercicio_siete() {
    char entrada[100];
    char *salida = nullptr;

    cout << "Ingrese una cadena: ";
    cin >> entrada;

    eliminarRepetidos(entrada, salida);

    cout << "Original: " << entrada << endl;
    cout << "Sin repetidos: " << salida << endl;

    delete[] salida;
}

int encontrar_estrellas(int **matriz, int filas, int columnas) {
    int estrellas = 0;

    for (int i = 1; i < filas - 1; i++) {
        for (int j = 1; j < columnas - 1; j++) {

            int suma = matriz[i][j] +
                       matriz[i][j-1] +
                       matriz[i][j+1] +
                       matriz[i-1][j] +
                       matriz[i+1][j];

            float promedio = suma / 5.0;

            if (promedio > 6) {
                estrellas++;
            }
        }
    }

    return estrellas;
}

void ejercicio_quince() {
    int filas, columnas;

    cout << "Ingrese filas: ";
    cin >> filas;
    cout << "Ingrese columnas: ";
    cin >> columnas;

    int **matriz = new int*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }

    cout << "Ingrese los valores:\n";
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cin >> matriz[i][j];
        }
    }

    int resultado = encontrar_estrellas(matriz, filas, columnas);

    cout << "Numero de estrellas: " << resultado << endl;

    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

bool comparar_cadenas(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (*a != *b) {
            return false;
        }
        a++;
        b++;
    }

    return (*a == '\0' && *b == '\0');
}

void ejercicio_tres() {
    char cadena1[100];
    char cadena2[100];

    cout << "Ingrese cadena 1: ";
    cin >> cadena1;

    cout << "Ingrese cadena 2: ";
    cin >> cadena2;

    if (comparar_cadenas(cadena1, cadena2)) {
        cout << "Son iguales" << endl;
    } else {
        cout << "Son diferentes" << endl;
    }
}

void problema_nueve() {
    int n;
    char cadena[200];

    cout << "Ingrese n: ";
    cin >> n;

    cout << "Ingrese cadena numerica: ";
    cin >> cadena;

    int len = strlen(cadena);
    int suma = 0;

    int i = len;

    while (i > 0) {
        int numero = 0;
        int potencia = 1;

        for (int j = 0; j < n; j++) {
            i--;

            if (i >= 0) {
                numero += (cadena[i] - '0') * potencia;
            }

            potencia *= 10;
        }

        suma += numero;
    }

    cout << "Original: " << cadena << endl;
    cout << "Suma: " << suma << endl;
}

void mostrar_sala(bool **sala, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (sala[i][j])
                cout << "+ ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}

void problema_once() {
    const int filas = 15;
    const int columnas = 20;

    bool **sala = new bool*[filas];
    for (int i = 0; i < filas; i++) {
        sala[i] = new bool[columnas];
        for (int j = 0; j < columnas; j++)
            sala[i][j] = false;
    }

    char opcion;
    do {
        mostrar_sala(sala, filas, columnas);

        cout << "R: Reservar, C: Cancelar, S: Salir: ";
        cin >> opcion;

        if (opcion == 'R' || opcion == 'C') {
            char fila_char;
            int asiento;

            cout << "Fila (A-O): ";
            cin >> fila_char;
            cout << "Asiento (1-20): ";
            cin >> asiento;

            int fila = fila_char - 'A';
            int col = asiento - 1;

            if (fila >= 0 && fila < filas && col >= 0 && col < columnas) {
                if (opcion == 'R')
                    sala[fila][col] = true;
                else
                    sala[fila][col] = false;
            }
        }

    } while (opcion != 'S');

    for (int i = 0; i < filas; i++)
        delete[] sala[i];
    delete[] sala;
}

void interseccion_rect(int A[4], int B[4], int C[4]) {
    int x1 = (A[0] > B[0]) ? A[0] : B[0];
    int y1 = (A[1] > B[1]) ? A[1] : B[1];

    int x2 = ((A[0] + A[2]) < (B[0] + B[2])) ? (A[0] + A[2]) : (B[0] + B[2]);
    int y2 = ((A[1] + A[3]) < (B[1] + B[3])) ? (A[1] + A[3]) : (B[1] + B[3]);

    if (x2 > x1 && y2 > y1) {
        C[0] = x1;
        C[1] = y1;
        C[2] = x2 - x1;
        C[3] = y2 - y1;
    } else {
        C[0] = C[1] = C[2] = C[3] = 0;
    }
}

void problema_quince_rect() {
    int A[4], B[4], C[4];

    cout << "Rectangulo A (x y ancho alto): ";
    for (int i = 0; i < 4; i++) cin >> A[i];

    cout << "Rectangulo B (x y ancho alto): ";
    for (int i = 0; i < 4; i++) cin >> B[i];

    interseccion_rect(A, B, C);

    cout << "Interseccion: { ";
    for (int i = 0; i < 4; i++)
        cout << C[i] << " ";
    cout << "}" << endl;
}


void problema_uno() {
    int dinero;

    cout << "Ingrese la cantidad de dinero: ";
    cin >> dinero;

    int n = 9;

    // Denominaciones dinámicas
    int *denominaciones = new int[n]{1000, 500, 200, 100, 50, 20, 10, 5, 1};

    int *cantidad = new int[n];

    for (int i = 0; i < n; i++) {
        cantidad[i] = dinero / denominaciones[i];
        dinero %= denominaciones[i];
    }

    cout << "\nDescomposicion:\n";

    for (int i = 0; i < n; i++) {
        cout << denominaciones[i] << ": " << cantidad[i] << endl;
    }

    delete[] denominaciones;
    delete[] cantidad;
}
