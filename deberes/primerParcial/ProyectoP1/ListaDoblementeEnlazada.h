#ifndef LISTADOBLEMENTEENLAZADA_H
#define LISTADOBLEMENTEENLAZADA_H

#include <iostream>
#include <string>

template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* anterior;
    Nodo<T>* siguiente;
    Nodo(const T& d) : dato(d), anterior(nullptr), siguiente(nullptr) {}
};

template <typename T>
class ListaDoblementeEnlazada {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tamano;

    Nodo<T>* buscarNodo(const std::string& id) const {
        for (Nodo<T>* n = cabeza; n != nullptr; n = n->siguiente)
            if (n->dato.getId() == id) return n;
        return nullptr;
    }

    ListaDoblementeEnlazada(const ListaDoblementeEnlazada&);
    ListaDoblementeEnlazada& operator=(const ListaDoblementeEnlazada&);

public:
    ListaDoblementeEnlazada() : cabeza(nullptr), cola(nullptr), tamano(0) {}

    ~ListaDoblementeEnlazada() {
        Nodo<T>* n = cabeza;
        while (n != nullptr) {
            Nodo<T>* sig = n->siguiente;
            delete n;
            n = sig;
        }
    }

    void agregar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (cola == nullptr) {
            cabeza = cola = nuevo;
        } else {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        tamano++;
    }

    bool eliminar(const std::string& id) {
        Nodo<T>* n = buscarNodo(id);
        if (n == nullptr) return false;

        if (n->anterior != nullptr) n->anterior->siguiente = n->siguiente;
        else                        cabeza = n->siguiente;

        if (n->siguiente != nullptr) n->siguiente->anterior = n->anterior;
        else                         cola = n->anterior;

        delete n;
        tamano--;
        return true;
    }

    T* buscar(const std::string& id) {
        Nodo<T>* n = buscarNodo(id);
        return (n != nullptr) ? &(n->dato) : nullptr;
    }

    const T* buscar(const std::string& id) const {
        Nodo<T>* n = buscarNodo(id);
        return (n != nullptr) ? &(n->dato) : nullptr;
    }

    template <typename F>
    void paraCada(F f) const {
        for (Nodo<T>* n = cabeza; n != nullptr; n = n->siguiente) f(n->dato);
    }

    void imprimir() const {
        if (cabeza == nullptr) { std::cout << "  (lista vacia)" << std::endl; return; }
        int i = 1;
        for (Nodo<T>* n = cabeza; n != nullptr; n = n->siguiente) {
            std::cout << "  " << i++ << ". ";
            n->dato.mostrar();
        }
    }

    int getTamano() const { return tamano; }
};

#endif
