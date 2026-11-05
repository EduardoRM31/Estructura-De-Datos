#include "Funciones.h"

template<typename T>
void intercambiar(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
T mayor(T a, T b){
    if(a > b){
        return a;
    }
    return b;
}