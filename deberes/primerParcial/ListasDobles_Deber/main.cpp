#include <iostream>
#include <string>
#include <limits>
using namespace std;
#include "nodo.h"

bool validarCedula(string cedula) {
    if(cedula.length() != 10) {
        return false;
    }

    for (char digito : cedula) {
        if (!(digito >= '0' && digito <= '9')) {
            return false;
        }
    }

    int codigoVerificador = cedula[9] - '0';
    int suma = 0, digito, codigoVerificadorCalculado;
    for(int i = 0; i < 9; i++){
        digito = cedula[i] - '0';
        if(i % 2 == 0){
            digito *= 2;
            if(digito > 9){
                digito -= 9;
            }
        }
        suma += digito;
    }

    codigoVerificadorCalculado = suma%10;
    if(codigoVerificadorCalculado != 0){
        codigoVerificadorCalculado = 10 - codigoVerificadorCalculado;
    }


    return codigoVerificador == codigoVerificadorCalculado;
}

bool validarLetras(string texto) {
    if (texto.empty()) {
        return false;
    }

    for (char letra : texto) {
        if (!((letra >= 'A' && letra <= 'Z') ||
              (letra >= 'a' && letra <= 'z'))) {
            return false;
        }
    }

    return true;
}

int main() {
    ListaDoble lista;
    int opcion;
    string cedula, nombre, apellido;

    do {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Insertar" << endl;
        cout << "2. Imprimir" << endl;
        cout << "3. Buscar" << endl;
        cout << "4. Borrar" << endl;
        cout << "5. Imprimir Reversa" << endl;
        cout << "6. Buscar por Apellido" << endl;
        cout << "7. Modificar un registro" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";

        if (!(cin >> opcion)) {
       cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

          cout << "Error, ingresar solo numeros" << endl;
          opcion = -1;
      continue;
      }
      
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (opcion) {
        case 1:
        do {
            cout << "Cedula: ";
            getline(cin,cedula);
            if (!validarCedula(cedula)) {
                cout << "Error, ingrese una cedula valida" << endl;
            }else if(lista.buscar(cedula) != nullptr) {
                cout << "Error. esa cedula ya esta registrada" << endl;
            }
        }while (!validarCedula(cedula) || lista.buscar(cedula) != nullptr);

            do {
                cout << "Nombre: ";
              getline(cin, nombre);

                if (!validarLetras(nombre)) {
                    cout << "Error, ingrese solo letras" << endl;
                }

            } while (!validarLetras(nombre));

            do {
                cout << "Apellido: ";  
              getline(cin, apellido);

                if (!validarLetras(apellido)) {
                    cout << "Error, ingrese solo letras" << endl;
                }

            } while (!validarLetras(apellido));

            lista.insertar(cedula, nombre, apellido);
            cout << "Registrado correctamente." << endl;
            break;

            case 2:
                if (lista.getCabeza() == nullptr)
                    cout << "La lista esta vacia." << endl;
                else
                    lista.imprimir();
                break;

            case 3: {
                if(lista.getCabeza()== nullptr){
                    cout << "La lista esta vacia."<< endl;
                    break;
                }
                cout << "Cedula a buscar: ";
                 getline(cin, cedula);
                 if(!validarCedula(cedula)){
                    cout <<"Cedula Invalida"<<endl;
                    break;
                 }
                Nodo* encontrado = lista.buscar(cedula);
                if (encontrado != nullptr)
                    cout << "Encontrado: " << encontrado->getNombre()
                         << " " << encontrado->getApellido() << endl;
                else
                    cout << "No existe esa cedula." << endl;
                break;
            }

            case 4:
            if (lista.getCabeza() == nullptr) {              // (2) lista vacia
                    cout << "La lista esta vacia." << endl;
                    break;
                }
                cout << "Cedula a borrar: ";
              getline(cin, cedula);
              if (!validarCedula(cedula)) {                    // (3) formato valido
                    cout << "Cedula invalida." << endl;
                    break;
                }

                if (lista.borrar(cedula))
                    cout << "Borrado." << endl;
                else
                    cout << "No existe esa cedula." << endl;
                break;
            case 5:
                if (lista.getCabeza() == nullptr) {
                    cout << "La lista esta vacia." << endl;
                } else {
                    cout << "\nLista en reversa:" << endl;
                    lista.imprimirReversa();
                }
                break;
            case 6:{
                int total = 0;
                if(lista.getCabeza()== nullptr){
                    cout << "La lista esta vacia" << endl;
                    break;
                }
                cout << "Apellido a buscar : "; 
                getline(cin,apellido);
                total = lista.buscarPorApellido(apellido);
                if (total == 0){
                    cout << "No hay personas con ese apellido registrado" << endl;
                }else {
                    cout << "Total encontrados: " << total << endl;
                }
                break;
            }
            case 7: {
                if (lista.getCabeza() == nullptr) {
                    cout << "La lista esta vacia." << endl;
                    break;
                }
                
                cout << "Ingrese la cedula del registro a modificar: ";
                getline(cin, cedula);
                
                if (!validarCedula(cedula)) {
                    cout << "Cedula invalida." << endl;
                    break;
                }

                lista.modificarRegistro(cedula);
                break;
            }
            case 0:
                cout << "Salir" << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);

    return 0;
}
