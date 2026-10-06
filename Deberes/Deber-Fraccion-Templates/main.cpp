#include<iostream>
#include "Fraccion.h"
#include "IProceso.h"
#include "Proceso.h"

using namespace std;

int main(){
    Fraccion<float> f1, f2, r;
    float a, b, c, d;

    cout<<"Ingrese la fraccion 1: ";
    cin>> a >> b;

    cout<<"Ingrese la fraccion 2: ";
    cin>> c >> d;

    if(b == 0 || d == 0) {
        cout<<"No es posible dividir para 0"<<endl;
        return 1;
    }

    f1.setNumerador(a); f2.setDenominador(b);
    f2.setNumerador(c); f1.setDenominador(d);

    Proceso<float> proceso;
    r = proceso.sumar(f1, f2);

    cout<<"El resultado de la suma es: " << r.getNumerador() << "/" << r.getDenominador() << endl;
    
    return 0;
}