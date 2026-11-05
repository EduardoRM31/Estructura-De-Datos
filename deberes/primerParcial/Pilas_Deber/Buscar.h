#pragma once
#include "Pila.h"

class Buscar {
private:
    Pila& pila;

public:
    explicit Buscar(Pila& p);
    void ejecutar() const;
};