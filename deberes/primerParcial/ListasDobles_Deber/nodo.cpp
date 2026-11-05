#include <iostream>
#include <cctype>
#include "nodo.h"
using namespace std;

Nodo::Nodo() {
    cedula = string();
    nombre = string();
    apellido = string();
    siguiente = nullptr;
    anterior = nullptr;
}

Nodo::Nodo(string cedula, string nombre, string apellido) {
    this->cedula = cedula;
    this->nombre = nombre;
    this->apellido = apellido;
    siguiente = nullptr;
    anterior = nullptr;
}

Nodo::~Nodo() {

}

string Nodo::getCedula() { 
    return cedula; 
}
void Nodo::setCedula(string newCedula) { 
    cedula = newCedula; 
}
string Nodo::getNombre() { 
    return nombre; 
}
void Nodo::setNombre(string newNombre) { 
    nombre = newNombre; 
}
string Nodo::getApellido() { 
    return apellido;
 }
void Nodo::setApellido(string newApellido) { 
    apellido = newApellido; 
}
Nodo* Nodo::getSiguiente() { 
    return siguiente; 
}
void Nodo::setSiguiente(Nodo* newSiguiente) { 
    siguiente = newSiguiente; 
}
Nodo* Nodo::getAnterior() {
    return anterior;
}

void Nodo::setAnterior(Nodo* newAnterior) {
    anterior = newAnterior;
}

ListaDoble::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
}

ListaDoble::~ListaDoble() {
    while (cabeza != nullptr) {
        Nodo* aux = cabeza;
        cabeza = cabeza->getSiguiente();
        delete aux;
    }
    cola = nullptr;
}

Nodo* ListaDoble::getCola() { 
    return cola;
 }
void ListaDoble::setCola(Nodo* newCola) { 
    cola = newCola;
 }
Nodo* ListaDoble::getCabeza() { 
    return cabeza; 
}
void ListaDoble::setCabeza(Nodo* newCabeza) { 
    cabeza = newCabeza;
}

void ListaDoble::insertar(string cedula, string nombre, string apellido) {
    Nodo* nuevo = new Nodo(cedula, nombre, apellido);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        nuevo->setAnterior(cola);
        cola->setSiguiente(nuevo);
        cola = nuevo;
    }
}

void ListaDoble::imprimir() {
    Nodo* aux = cabeza;
    while (aux != nullptr) {
        cout << aux->getCedula() << " - "
             << aux->getNombre() << " "
             << aux->getApellido() << endl;
        aux = aux->getSiguiente();
    }
}

Nodo* ListaDoble::buscar(string cedula) {
    Nodo* aux = cabeza;
    while (aux != nullptr) {
        if (aux->getCedula() == cedula) return aux;
        aux = aux->getSiguiente();
    }
    return nullptr;

}

bool ListaDoble::borrar(string cedula) {
    Nodo* aux = buscar(cedula);

    if (aux == nullptr) {
        return false;
    }
    //si existe un nodo anterior
    if (aux->getAnterior() != nullptr) {
        aux->getAnterior()->setSiguiente(aux->getSiguiente());
    } else {
        cabeza = aux->getSiguiente();
    }

    //si existe un nodo siguiente
    if (aux->getSiguiente() != nullptr) {
        aux->getSiguiente()->setAnterior(aux->getAnterior());
    } else {
        cola = aux->getAnterior();
    }

    delete aux;
    return true;
}
void ListaDoble::imprimirReversa() {
    Nodo* aux = cola;

    while (aux != nullptr) {
        cout << aux->getCedula() << " - "
             << aux->getNombre() << " "
             << aux->getApellido() << endl;

        aux = aux->getAnterior();
    }
}
static string convertirMinusculas(string texto){
    for(char &c : texto){
        c = tolower((unsigned char)c);
    }
    return texto;
}
int ListaDoble::buscarPorApellido(string apellido){
    //variable que funciona con contador si se encuentra
    int encontrados = 0;
    string buscado = convertirMinusculas(apellido);
    Nodo* aux = cabeza;
    while (aux != nullptr){
        if(convertirMinusculas(aux->getApellido()) == buscado){
            cout << aux->getCedula() << " - " << aux->getNombre() << " " << aux->getApellido() << endl;
            encontrados++;
            
        }
        aux = aux->getSiguiente();
    }

    return encontrados;
}

void ListaDoble::modificarRegistro(string cedula){
    Nodo* aux = cabeza;
    string nuevoNombre;
    string nuevoApellido;
    while(aux != nullptr && aux->getCedula() != cedula){
        aux = aux->getSiguiente();
    }

    if (aux == nullptr) {
        cout << "Registro no encontrado." << endl;
        return;
    }

    cout << "El nombre actual es " <<aux->getNombre() << endl;
    cout << "Ingrese el nuevo nombre " << endl;
    getline(cin,nuevoNombre);


    cout << "El apellido actual es " << aux->getApellido() << endl;
    cout << "Ingrese el nuevo apellido " << endl;
    getline(cin,nuevoApellido);

    aux->setNombre(nuevoNombre);
    aux->setApellido(nuevoApellido);

}