#ifndef NODO_H
#define NODO_H

#include "Persona.h"

class Nodo {
private:
    Persona persona;
    Nodo* siguiente;

public:
    Nodo();
    Nodo(const Persona& persona, Nodo* siguiente = nullptr);
    ~Nodo();

    Persona getPersona() const;
    void setPersona(const Persona& persona);

    Nodo* getSiguiente() const;
    void setSiguiente(Nodo* siguiente);
};

#endif