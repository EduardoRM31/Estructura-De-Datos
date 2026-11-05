#pragma once
#include "Pila.h"
#include <string>

class Insertar {
private:
    Pila& pila;

public:
    explicit Insertar(Pila& p);
    void ejecutar();

private:
    std::string ingresarLetras();   // método de la clase
};
