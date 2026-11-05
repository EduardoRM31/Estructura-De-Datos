#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;


inline string ordinal(int n){
    const char* nombres[] = {"", "primero", "segundo", "tercero", "cuarto", "quinto", "sexto", "septimo", "octavo", "noveno", "decimo"};

    if(n >= 1 && n <= 10) return nombres[n];

    return "numero " + to_string(n);
}

template<typename T>
class Nodo{
    public:
    T dato;
    Nodo<T>* siguiente;

    Nodo(T dato){
        this->dato = dato;
        siguiente = nullptr;
    }
};

template<typename T>
class Cola{
    private:
    Nodo<T>* frente;
    Nodo<T>* fin;
    int contadorId;


    bool existe(T dato){
        Nodo<T>* actual = frente;
        while(actual != nullptr){
            if(actual->dato == dato) return true;
            actual = actual->siguiente;
        }
        return false;
    }

public:
    Cola() {
        frente = nullptr;
        fin = nullptr;
        contadorId = 0;
    }

    Cola(const Cola&) = delete;
    Cola& operator=(const Cola&) = delete; //No se dupliquen colas

    ~Cola() {
        while (frente != nullptr) {
            Nodo<T>* aux = frente;
            frente = frente->siguiente;
            delete aux;
        }
    }

    bool estaVacia() {
        return frente == nullptr;
    }

    void insertar(T dato){
        if(existe(dato)){
            throw invalid_argument("Ya existe una persona registrada con esa cedula.");
        }
        contadorId++;
        dato.setId(contadorId);

        Nodo<T>* nuevo = new Nodo<T>(dato);
        if(estaVacia()){
            frente = nuevo;
            fin = nuevo;
        } else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }
        cout<<"Insertado correctamente con ID " << contadorId << endl;
    }

    bool buscar(T dato){
        Nodo<T>* actual = frente;
        while(actual != nullptr){
            if(actual->dato == dato){
                cout<<"Encontrado: " << actual->dato <<endl;
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void imprimir(){
        if(estaVacia()){
            cout<<"La cola esta vacia."<<endl;
            return;
        }

        Nodo<T>* actual = frente;
        int posicion = 1;
        while(actual != nullptr){
            cout<< posicion << ". " << actual->dato <<endl;
            actual = actual->siguiente;
            posicion++;
        }
    }

    void eliminar(){
        if(estaVacia()){
            throw runtime_error("La cola esta vacia, no hay nadie que eliminar.");
        }

        Nodo<T>* aux = frente;
        cout<<"Eliminado: "<< aux->dato <<endl;
        frente = frente->siguiente;
        if(frente == nullptr){
            fin = nullptr;
        }
        delete aux;
    }

    void cedulaPichincha(){
        Nodo<T>* actual = frente;
        int contador = 0;

        while(actual != nullptr){
            if(actual->dato.getCedula().substr(0, 2) == "17"){ 
                cout<< actual->dato << endl;
                contador++;
            }
            actual = actual->siguiente;
        }

        if(contador == 0){
            cout<<"No hay cedulas de Pichincha registradas."<<endl;
        } else {
            cout<<"Total: " <<contador <<endl;
        }
    }

    void explicarCola(){
        if(estaVacia()){
            throw runtime_error("La cola esta vacia, no hay nada que explicar.");
        }

        cout<<endl;
        Nodo<T>* actual = frente;
        int turno = 1;

        while(actual != nullptr){
            cout<<actual->dato.getNombre()<<" "<<actual->dato.getApellido()
                <<" (cedula "<<actual->dato.getCedula()<<") se registro con el ID "
                <<actual->dato.getId()<<" y fue atendido "<<ordinal(turno)<<"."<<endl;
            actual = actual->siguiente;
            turno++;
        }

        cout<<endl;
        cout<<"Frente de la cola: "<<frente->dato.getNombre()<<" "<<frente->dato.getApellido()
            <<" (ID "<<frente->dato.getId()<<")"<<endl;
        cout<<"Fin de la cola: "<<fin->dato.getNombre()<<" "<<fin->dato.getApellido()
            <<" (ID "<<fin->dato.getId()<<")"<<endl;
    }

    bool modificar(string cedula, string nombre, string apellido){
        Nodo<T>* actual = frente;
        while(actual != NULL){
            if(actual->dato.getCedula() == cedula){
                actual->dato.setNombre(nombre);
                actual->dato.setApellido(apellido);
                cout<<"Modificado: " << actual->dato <<endl;
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void buscarApellido(string apellido){
        Nodo<T>* actual = frente;
        int contador = 0;

        while(actual != nullptr){
            if(actual->dato.getApellido() == apellido){
                cout<< actual->dato << endl;
                contador++;
            }
            actual = actual->siguiente;
        }

        if(contador == 0){
            cout<<"No hay personas con ese apellido registradas."<<endl;
        } else {
            cout<<"Total: " <<contador <<endl;
        }
    }

    template<typename F>
    void recorrer(F accion){
        Nodo<T>* actual = frente;
        while(actual != nullptr){
            accion(actual->dato);
            actual = actual->siguiente;
        }
    }
};

#endif