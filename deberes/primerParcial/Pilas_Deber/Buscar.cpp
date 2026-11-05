#include "Buscar.h"
#include <iostream>
#include <string>

Buscar::Buscar(Pila& p) : pila(p) {}

void Buscar::ejecutar() const {
    if (pila.estaVacia()) {
        std::cout << "La pila esta vacia. No hay elementos para buscar.\n";
        return;
    }

    std::string cedula;
    std::cout << "Ingrese la cedula a buscar: ";
    std::cin >> cedula;

    pila.buscar(cedula);
}