#include <iostream>

//Declaro las variables temporales que voy a usar a nivel global.

int i,aux,n;


using namespace std;

void problema_dos(){

    cout <<"Ingresa tu plata porfavor." <<endl;
    cin >>n;

    cout << "\n BILLETES \n";

    int cant_50000 = n / 50000;
    n = n % 50000;
    cout << "50000: " << cant_50000 << endl;

    int cant_20000 = n / 20000;
    n = n % 20000;
    cout << "20000: " << cant_20000 << endl;

    int cant_10000 = n / 10000;
    n = n % 10000;
    cout << "10000: " << cant_10000 << endl;

    int cant_5000 = n / 5000;
    n = n % 5000;
    cout << "5000: " << cant_5000 << endl;

    int cant_2000 = n / 2000;
    n = n % 2000;
    cout << "2000: " << cant_2000 << endl;

    int cant_1000 = n / 1000;
    n = n % 1000;
    cout << "1000: " << cant_1000 << endl;

    cout << "\n MONEDAS \n";

    int cant_500 = n / 500;
    n = n % 500;
    cout << "500: " << cant_500 << endl;

    int cant_200 = n / 200;
    n = n % 200;
    cout << "200: " << cant_200 << endl;

    int cant_100 = n / 100;
    n = n % 100;
    cout << "100: " << cant_100 << endl;

    int cant_50 = n / 50;
    n = n % 50;
    cout << "50: " << cant_50 << endl;

    cout << "\n" << endl;
    cout << "Faltante: " << n << endl;
}

void problema_cuatro(){}

void problema_seis(){

        int n;
        float e = 1.0;        // Empezamos con 1 por que 1 factorial 0 es 1 asi que pues xd.
        float factorial = 1.0;

        cout << "Ingrese el numero de aproximacion de euler: ";
        cin >> n;

        for(int i = 1; i <= n; i++) {

            factorial *= i;
            e += 1.0 / factorial;

            cout << i << "! = " << factorial << endl;
        }

        cout << "Aproximacion de e: " << e << endl;

    }

void problema_ochov1(){
    // Este es mi codigo hecho de mi mente, sufrimiento y dolor, pipipi, voy a hacer otra funcion,
    //quitandole la depuracion y organizando el break del
    //segundo for.

    int a,b,c,sumatoria_aux = 0, sumatoria_a = 0, sumatoria_b = 0;

    cout <<"Ingrese un numero a: " <<endl;
    cin >> a;
    cout <<"Ingrese un numero b: " <<endl;
    cin >>b;
    cout <<"Ingrese un numero tope C: " <<endl;
    cin >> c;

    for(int u = 1; u<=c; u++){
        sumatoria_aux = a*u;

        cout <<"Sumatoria de a: " << sumatoria_a <<endl;  // para depuracion a ver si mi codigo si codifica joe.

        if(sumatoria_aux <=c){
            sumatoria_a += sumatoria_aux;

            cout <<"\nNumero sumado es : "<< sumatoria_aux <<endl;
            cout << "\n" << u << " sumatoria " << sumatoria_aux <<endl;
        }
         else{
          break;
          }

        }

    for(int u = 1; u<=c; u++){

      sumatoria_aux = b*u;

        cout <<"\nSumatoria de b: " << sumatoria_aux <<endl; // para depuracion xda.

        if(sumatoria_aux<=c && (sumatoria_aux %a !=0)){
          sumatoria_b += sumatoria_aux;

            cout <<"\nNumero sumado no repetido. : " << sumatoria_aux;
            cout << "\n" << u << " sumatoria " << sumatoria_aux <<endl;

        }
        else{
          break;
        }
        }
    cout <<"La sumatoria total de los numeros essssssssssssss: " << sumatoria_a+sumatoria_b <<endl;
    }

void problema_ochoVfinal(){
    //Simplificacion de variables, se quita las depuraciones de codigo, se mejora la logica del for del segundo ciclo.
    int a,b,c, multiplo = 0, sumaa=0, sumab=0;
    cout <<"Ingrese un numero a: " <<endl;
    cin >> a;
    cout <<"Ingrese un numero b: " <<endl;
    cin >>b;
    cout <<"Ingrese un numero tope C: " <<endl;
    cin >> c;

    for(int u = 1; u<=c; u++){
        multiplo = a*u;

        if(multiplo <=c){
            sumaa += multiplo;
            cout << multiplo <<"+ " <<endl;
        }
        else{
            break;
        }
    }
    for(int u = 1; u<=c; u++){
        multiplo = b*u;

        if(multiplo<=c && (multiplo %a !=0)){
            sumab += multiplo;

            cout <<multiplo << "+" <<endl;
        }

        if (multiplo >c){
            break;
        }
    }
    cout << sumaa+sumab <<endl;
    cout <<"\nTotal de la sumatoria: " <<sumaa+sumab <<endl;
}

void problema_diez(){

    int a;

    cout <<"Ingrese el enesimo numero primo desea calcular: ";
    cin >>a;

    int contador = 0;
    int numero = 2;

    while(contador < a){

        bool primo = true;

        for(int i = 2; i < numero; i++){
            if(numero % i == 0){
                primo = false;
                break;
            }
        }

        if(primo){
            contador++;
        }

        if(contador == a){
            cout << "El primo numero " << a << " es: " << numero << endl;
            break;
        }

        numero++;
    }

    }

void problema_doce(){

    int n;
    int mayorFactor = 0;

    cout << "Ingrese un numero: ";
    cin >> n;

    int i = 2;

    while(n > 1){

        if(n % i == 0){
            mayorFactor = i;
            n = n / i;
        }else{
            i++;
        }

    }

    cout << "El mayor factor primo es: " << mayorFactor << endl;
;
}

bool esPalindromo(int n){
 int original = n;
    int invertido = 0;
    while (n > 0) {
        invertido = invertido * 10 + n % 10;
        n /= 10;
    }
    return original == invertido;
}
void problema_catorce(){
    int mayorPalindromo = 0;
    int factor1 = 0, factor2 = 0;

    for (int i = 999; i >= 100; i--) {
        for (int j = i; j >= 100; j--) {
            int producto = i * j;
            if (producto <= mayorPalindromo)
                break;
            if (esPalindromo(producto))
            {
                mayorPalindromo = producto;
                factor1 = j;
                factor2 = i;
            }
        }
    }
    cout << factor1 << "*" << factor2 << "=" << mayorPalindromo << endl;
}

void conjetura(int x){
    cout << x <<" ";
    if (x>1){
        if(x%2==0){
            conjetura(x/2);
        }
        else{
            conjetura(x+x+x+1);
        }
    }
}
void problema_dieciseis(){

    int x = 0;

    cout <<"Ingresa tu numero semilla porfavor: " <<endl;
    cin >> x;
    conjetura(x);
}


int main(){

    int opcion;

    void (*ejercicios[8])()={
    problema_dos, problema_seis, problema_ochoVfinal, problema_diez, problema_doce, problema_catorce, problema_dieciseis
    };

    cout <<"Ingrese el ejercicio que quiere seleccionar porfavor: ";
    cin >> opcion;

    if(opcion>=1 && opcion <=16){
        ejercicios[opcion-1]();
    }
    else{
        cout <<"Opcion invalida pa.\n" <<endl;
    }
    return 0;
}


