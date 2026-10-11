#include <iostream>
#include "Fraccion.h"
#include "IProceso.h"
#include "Proceso.h"

using namespace std;

int main(){
	Fraccion f1, f2, r;
	float a, b, c, d;
	
	cout<<"Fraccion 1: ";
	cin>> a >> b;
	
	cout<<"Fraccion 2: ";
	cin>> c >> d;
	
	if(b == 0 || d == 0){
		cout<<"El denominador no puede ser 0."<< endl;
		return 1;
	}
	
	f1.setNumerador(a); f1.setDenominador(b);
	f2.setNumerador(c); f2.setDenominador(d);
	
	Proceso proceso;
	r = proceso.sumar(f1, f2);
	
	cout << f1.getNumerador() << "/" << f1.getDenominador() << " + " << f2.getNumerador() << "/" << f2.getDenominador() << " = "
         << r.getNumerador() << "/" << r.getDenominador() << endl;
    return 0;
}