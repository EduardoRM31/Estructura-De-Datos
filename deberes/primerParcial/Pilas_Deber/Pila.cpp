#include "Pila.h"
#include <iostream>

Pila::Pila() : tope(nullptr) {}

bool Pila::estaVacia() const {
    return tope == nullptr;
}

void Pila::push(const Persona& persona) {
    Nodo* actual = tope;
    while (actual != nullptr) {
        if (actual->getPersona().getCedula() == persona.getCedula()) {
            std::cout << "Error: Ya existe una persona con esa cedula en la pila.\n";
            return;
        }
        actual = actual->getSiguiente();
    }

    Nodo* nuevo = new Nodo(persona, tope);
    tope = nuevo;
    std::cout << "Persona ingresada con exito.\n";
}

Persona Pila::pop() {
    if (estaVacia()) {
        std::cout << "La pila esta vacia.\n";
        return Persona();
    }
    Nodo* aux = tope;
    Persona personaEliminada = aux->getPersona();
    tope = tope->getSiguiente();
    delete aux;
    return personaEliminada;
}

void Pila::buscar(const std::string& cedula) const {
    if (estaVacia()) {
        std::cout << "La pila esta vacia.\n";
        return;
    }

    Nodo* actual = tope;
    bool encontrado = false;

    while (actual != nullptr) {
        if (actual->getPersona().getCedula() == cedula) {
            std::cout << "\n[PERSONA ENCONTRADA]\n";
            actual->getPersona().mostrar();
            encontrado = true;
            break;
        }
        actual = actual->getSiguiente();
    }

    if (!encontrado) {
        std::cout << "No se encontro ningun registro con la cedula: " << cedula << "\n";
    }
}

void Pila::mostrar() const {
    if (estaVacia()) {
        std::cout << "La pila esta vacia.\n";
        return;
    }

    Nodo* actual = tope;
    std::cout << "\n=== CONTENIDO DE LA PILA ===\n";
    while (actual != nullptr) {
        actual->getPersona().mostrar();
        actual = actual->getSiguiente();
    }
    std::cout << "============================\n";
}

int Pila::contarElementos() const {
    int contador = 0;
    Nodo* actual = tope;
    while (actual != nullptr) {
        contador++;
        actual = actual->getSiguiente();
    }
    return contador;
}

void Pila::verTope() const {
    if (estaVacia()) {
        std::cout << "La pila esta vacia. No hay nadie en el tope.\n";
        return;
    }
    std::cout << "\n=== PERSONA EN EL TOPE ===\n";
    tope->getPersona().mostrar();
}

void Pila::vaciarPila() {
    if (estaVacia()) {
        std::cout << "La pila ya esta vacia.\n";
        return;
    }
    while (!estaVacia()) {
        pop();
    }
    std::cout << "Se han eliminado todos los elementos de la pila.\n";
}
void Pila::voltearPila(){

    if(estaVacia()){
        std::cout << "La pila ya esta vacia.\n";
        return;
    }
    Nodo* anterior = nullptr;
    Nodo* actual = tope;
    Nodo* siguiente = nullptr;

    while(actual != nullptr){
            siguiente = actual -> getSiguiente();
            actual -> setSiguiente(anterior);
            anterior = actual;
            actual = siguiente;
    }
    tope = anterior;
}

void Pila::mostrarApellidosOrdenados() const {
    if (estaVacia()) {
        std::cout << "La pila esta vacia.\n";
        return;
    }

    int total = contarElementos();
    std::string* apellidos = new std::string[total];   
    int* cantidades = new int[total];                  

    Nodo* actual = tope;
    int i = 0;
    while (actual != nullptr) {
        apellidos[i] = actual->getPersona().getApellido();
        cantidades[i] = static_cast<int>(apellidos[i].length());
        actual = actual->getSiguiente();
        i++;
    }

    for (int pasada = 0; pasada < total - 1; pasada++) {
        for (int j = 0; j < total - 1 - pasada; j++) {
            if (cantidades[j] > cantidades[j + 1]) {
                int auxCantidad = cantidades[j];
                cantidades[j] = cantidades[j + 1];
                cantidades[j + 1] = auxCantidad;

                std::string auxApellido = apellidos[j];
                apellidos[j] = apellidos[j + 1];
                apellidos[j + 1] = auxApellido;
            }
        }
    }

    std::cout << "\n=== APELLIDOS ORDENADOS POR NUMERO DE CARACTERES ===\n";
    for (int k = 0; k < total; k++) {
        std::cout << apellidos[k] << " : " << cantidades[k] << "\n";
    }
    std::cout << "====================================================\n";

    delete[] apellidos;
    delete[] cantidades;
}

Pila::~Pila() {
    vaciarPila();
}