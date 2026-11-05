#include "Eliminar.h"
#include <iostream>

Eliminar::Eliminar(Pila& p) : pila(p) {}

void Eliminar::ejecutar() {
    if (pila.estaVacia()) {
        std::cout << "La pila esta vacia, no hay nada que eliminar.\n";
        return;
    }

    Persona eliminada = pila.pop();
    std::cout << "Persona eliminada:\n";
    eliminada.mostrar();
}