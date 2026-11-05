#include "Imprimir.h"

Imprimir::Imprimir(Pila& p) : pila(p) {}

void Imprimir::ejecutar() const {
    pila.mostrar();
}