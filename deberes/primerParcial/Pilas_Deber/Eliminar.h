#pragma once
#include "Pila.h"

class Eliminar {
private:
    Pila& pila;

public:
    explicit Eliminar(Pila& p);
    void ejecutar();
};