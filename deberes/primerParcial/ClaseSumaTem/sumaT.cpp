#include <iostream>
#include "sumaT.h"

using namespace std;

int main() {
    sumaT<int> sumaT1(4, 1);
    sumaT<float> sumaT2(4.5f, 2.4f);

    sumaT1.sumar(4, 1);
    cout << endl;
    sumaT2.sumar(4.5f, 2.4f);
    cout << endl;
    return 0;
}

//5 ejercicios de template, hacer todo separado .cpp, .h, cualquier ejercicio, tener listo el de fraccion
//y estudiar metodos sobrecargados