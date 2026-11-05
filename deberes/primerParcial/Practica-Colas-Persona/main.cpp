#include "Persona.h"
#include "Nodo.h"
#include <iostream>

using namespace std;

int main(){
    Cola<Persona> cola;

    int opcion;

    string nombre, cedula, apellido;

    do{
        cout<<"=====MENU====="<<endl;
        cout<<"1. Insertar"<<endl;
        cout<<"2. Buscar"<<endl;
        cout<<"3. Imprimir"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Cedulas de Pichincha"<<endl;
        cout<<"6. Salir"<<endl;
        cout<<"Ingrese una opcion: "; cin>>opcion;

        switch (opcion){
        case 1:
            cout<< "Cedula: "; cin>>cedula;
            cout<< "Nombre: "; cin>>nombre;
            cout<< "Apellido: "; cin>>apellido;
            cola.insertar(Persona(cedula, nombre, apellido));
            break;
        case 2:
            cout<<"Ingrese la cedula: "<<endl;
            cin>>cedula;
            if(!cola.buscar(Persona(cedula, "", ""))){
                cout<<"No se encontro ese numero de cedula"<<endl;
            }
            break;
        case 3:
            cola.imprimir();
            break;
        case 4:
            cola.eliminar();
            break;
        case 5:
            cola.cedulaPichincha();
            break;
        case 6:
            cout<<"SALIENDO.."<<endl;
            return 0;
        default:
            cout<<"Opcion no valida"<<endl;
            break;
        }
    }while (opcion != 6);
}