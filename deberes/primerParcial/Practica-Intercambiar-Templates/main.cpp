#include <iostream>
#include <string>
#include "Funciones.h"

using namespace std;

int main(){
    int a = 3, b = 7;
    intercambiar(a, b);
    cout<<"a=" << a << "b=" << b << endl;

    float f1 = 3.14f, f2 = 3.15f;
    intercambiar(f1, f2);
    cout<<"f1=" << f1 << "f2=" << f2 << endl;
}