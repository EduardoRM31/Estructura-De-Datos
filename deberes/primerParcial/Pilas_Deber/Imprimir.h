#pragma once
#include "Pila.h"

class Imprimir {
private:
    Pila& pila;

public:
    explicit Imprimir(Pila& p);
    void ejecutar() const;
};