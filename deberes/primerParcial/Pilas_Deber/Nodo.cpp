#include "Nodo.h"

Nodo::Nodo() : persona(), siguiente(nullptr) {}
Nodo::Nodo(const Persona& persona, Nodo* siguiente) : persona(persona), siguiente(siguiente) {}
Nodo::~Nodo() {}

Persona Nodo::getPersona() const {
    return persona;
}
void Nodo::setPersona(const Persona& persona) {
    this->persona = persona;
}

Nodo* Nodo::getSiguiente() const {
    return siguiente;
}
void Nodo::setSiguiente(Nodo* siguiente) {
    this->siguiente = siguiente;
}
