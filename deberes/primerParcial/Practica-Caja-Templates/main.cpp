#include <iostream>
#include <string>
#include "caja.h"

using namespace std;

int main(){
    Caja<int> entero(10);
    Caja<double> doble(13.334);
    Caja<char> caracter('b');
    Caja<string> cadena("eduardo");

    entero.mostrar();
    doble.mostrar();
    caracter.mostrar();
    cadena.mostrar();

    entero.setValor(50);
    cout<<"Entero despues del set: " << entero.getValor() << endl;

    Caja<int> d1;
    Caja<string> d2;

    cout<<"d1 por defecto: " << d1.getValor() << endl;
    cout<<"d2 por defecto: [" << d2.getValor() << "]" << endl;

    return 0;
}