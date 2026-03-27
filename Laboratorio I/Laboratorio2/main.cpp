#include <iostream>
#include "utilidades.h"

using namespace std;

struct Opcion {
    int id;
    void (*func)();
};

int main() {

    Opcion menu[] = {
        {9, problema_nueve},
        {11, problema_once},
        {15, problema_quince_rect},
        {3, ejercicio_tres},
        {5, ejercicio_cinco},
        {7, ejercicio_siete},
        {13, ejercicio_quince},
        {17, problema_diecisiete},
    };

    int n = sizeof(menu) / sizeof(menu[0]);

    int opcion;

    do {
        cout << "\n--- MENU ---\n";
        cout << "3. Problema 3\n";
        cout << "5. Problema 5\n";
        cout << "7. Problema 7\n";
        cout << "9. Problema 9\n";
        cout << "11. Problema 11\n";
        cout << "13. Problema 13\n";
        cout << "15. Problema 15\n";
        cout << "17. Problema 17\n";

        cout << "0. Salir\n";

        cout << "Seleccione: ";
        cin >> opcion;

        bool encontrado = false;

        for (int i = 0; i < n; i++) {
            if (menu[i].id == opcion) {
                menu[i].func();
                encontrado = true;
                break;
            }
        }

        if (!encontrado && opcion != 0)
            cout << "Opcion no valida\n";

    } while (opcion != 0);

    return 0;
}
