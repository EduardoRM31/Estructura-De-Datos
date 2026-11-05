#ifndef NODO_H
#define NODO_H

#include <iostream>
using namespace std;

template<typename T>
class Nodo{
    public:
    T dato;
    Nodo<T>* siguiente;

    Nodo(T dato){
        this->dato = dato;
        siguiente = NULL;
    }
};

template<typename T>
class Cola{
    private:
    Nodo<T>* frente;
    Nodo<T>* fin;

public:
    Cola() {
        frente = NULL;
        fin = NULL;
    }

    ~Cola() {
        while (frente != NULL) {
            Nodo<T>* aux = frente;
            frente = frente->siguiente;
            delete aux;
        }
    }

    bool estaVacia() {
        return frente == NULL;
    }

    void insertar(T dato){
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if(estaVacia()){
            frente = nuevo;
            fin = nuevo;
        } else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }
        cout<<"Insertado correctamente" << endl;
    }

    bool buscar(T dato){
        Nodo<T>* actual = frente;
        while(actual != NULL){
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
        while(actual != NULL){
            cout<< posicion << ". " << actual->dato <<endl;
            actual = actual->siguiente;
            posicion++;
        }
    }

    void eliminar(){
        if(estaVacia()){
            cout<<"La cola esta vacia."<<endl;
            return;
        }

        Nodo<T>* aux = frente;
        cout<<"Eliminado: "<< aux->dato <<endl;
        frente = frente->siguiente;
        if(frente == NULL){
            fin = NULL;
        }
        delete aux;
    }

    void cedulaPichincha(){
        Nodo<T>* actual = frente;
        int contador = 0;

        while(actual != NULL){
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
};

#endif