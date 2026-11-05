#ifndef PILA_H
#define PILA_H

#include "Nodo.h"
#include "Persona.h"
#include <string>

class Pila {
private:
    Nodo* tope;

public:
    Pila();
    ~Pila();

    bool estaVacia() const;
    void push(const Persona& persona);
    Persona pop();
    void buscar(const std::string& cedula) const;
    void mostrar() const;

    int contarElementos() const;
    void verTope() const;
    void vaciarPila();
    void voltearPila();
    void mostrarApellidosOrdenados() const;
};

#endif