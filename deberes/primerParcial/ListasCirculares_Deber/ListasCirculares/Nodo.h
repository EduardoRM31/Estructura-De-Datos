#pragma once

#include "Persona.h"

#include <iostream>

using namespace std;

class Nodo {
private:
    Persona persona;
    Nodo* siguiente;
    Nodo* anterior; 

public:
    Nodo();
    Nodo(const Persona& persona, Nodo* siguiente = nullptr, Nodo* anterior = nullptr);

    Persona getPersona() const;
    Nodo* getSiguiente() const;
    Nodo* getAnterior() const;
    
    void setPersona(const Persona& persona);
    void setSiguiente(Nodo* siguiente);
    void setAnterior(Nodo* anterior);


    static void insertar(Nodo*& cabeza, const string& cedula, const string& nombre, const string& apellido);
    static void buscarPorCedula(Nodo* inicio, const string& cedulaBuscada);
    static bool contiene(Nodo* inicio, const string& valor);
    static void eliminar(Nodo*& cabeza, Nodo*& cola, const string& cedula);
    void Imprimir(Nodo* cabeza) const;
    void ImprimirReverso(Nodo* cabeza) const; 
    static void modificar(Nodo* inicio, const string& cedulaBuscada);
    static int contarNodos(Nodo* cabeza);
    static void liberarLista(Nodo*& cabeza);
};