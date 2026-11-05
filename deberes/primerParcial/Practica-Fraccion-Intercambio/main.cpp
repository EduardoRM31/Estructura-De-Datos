#include <iostream>

using namespace std;

template<typename T>
class Fraccion{
    private:
    T numerador;
    T denominador;

    public:
    Fraccion(){
    }

    ~Fraccion(){
    }

    Fraccion(T num, T den){
        this->numerador = num;
        this->denominador = den;
    }

    T getNumerador(){
        return numerador;
    }

    T getDenominador(){
        return denominador;
    }

    void setNumerador(T num){
        numerador = num;
    }

    bool setDenominador(T den){
        if(den == 0){
            cout << "No divisible: el denominador no puede ser 0" << endl;
            return false;
        }
        denominador = den;
        return true;
    }

    void invertir(){
        T aux = numerador;
        numerador = denominador;
        denominador = aux;
    }

    void imprimir(){
        cout<< "Original: " <<" " << numerador << " /" << " " << denominador << endl;
        invertir();
        cout<< "Invertido: " <<" " << numerador << " /" << " " << denominador << endl;
    }
};


int main(){
    float numerador, denominador;

    cout<<"Numerador: ";
    cin>>numerador;
    cout<<"Denominador: ";
    cin>>denominador;

    Fraccion<float> F1(numerador, denominador);

    F1.imprimir();
}