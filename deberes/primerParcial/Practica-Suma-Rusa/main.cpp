#include <iostream>

using namespace std;

int sumaS(int a, int b){
    int resultado = 0;
    for(int i = 0; i < b; i++){
        resultado = resultado + a; 
    }
    return resultado;
}

int main(){
    int a, b;
    int total = 0;

    cout<<"Ingrese a: ";
    cin>>a;

    cout<<"Ingrese b: ";
    cin>>b;

    total = sumaS(a, b);

    cout<<"La suma sucesiva de la multiplicacion es: " << total << endl;
}