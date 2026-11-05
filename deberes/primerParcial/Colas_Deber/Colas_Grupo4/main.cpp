#include "Persona.h"
#include "Nodo.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

string leerLinea(const string& mensaje){
    string linea;
    cout << mensaje;
    getline(cin, linea);   
    return linea;
}

int leerEntero(const string& mensaje){
    string s = leerLinea(mensaje);
    if(s.empty()) throw invalid_argument("Debe ingresar un numero.");
    for(size_t i = 0; i < s.size(); i++){
        if(!isdigit((unsigned char)s[i])) throw invalid_argument("Debe ingresar un numero entero positivo.");
    }
    if(s.size() > 6) throw invalid_argument("El numero es demasiado grande.");
    return stoi(s);
}


template<typename F>
string pedirValidado(const string& mensaje, F validar){
    while(true){
        string dato = leerLinea(mensaje);
        try{
            validar(dato);
            return dato;
        } catch(const invalid_argument& e){
            cout<<"Error: "<<e.what()<<" Intente de nuevo."<<endl;
        }
    }
}

int main(){
    Cola<Persona> cola;
    int opcion = 0;

    do{
        cout<<endl<<"MENU"<<endl;
        cout<<"1. Insertar"<<endl;
        cout<<"2. Buscar por cedula"<<endl;
        cout<<"3. Imprimir"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Cedulas de Pichincha"<<endl;
        cout<<"6. Explicar cola"<<endl;
        cout<<"7. Modificar persona"<<endl;
        cout<<"8. Buscar por apellido"<<endl;
        cout<<"9. Mostrar nombre completos"<<endl;
        cout<<"10. Salir"<<endl;

        try{
            opcion = leerEntero("Ingrese una opcion: ");

            switch (opcion){
            case 1:{
                string cedula = pedirValidado("Cedula: ", Persona::validarCedula);
                string nombre = pedirValidado("Nombre: ", [](const string& s){ Persona::validarTexto(s, "El nombre"); });
                string apellido = pedirValidado("Apellido: ", [](const string& s){ Persona::validarTexto(s, "El apellido"); });

                cola.insertar(Persona(cedula, nombre, apellido));
                break;
            }
            case 2:{
                string cedula = pedirValidado("Ingrese la cedula: ", Persona::validarCedula);
                if(!cola.buscar(Persona(cedula, "", ""))){
                    cout<<"No se encontro ese numero de cedula"<<endl;
                }
                break;
            }
            case 3:
                cola.imprimir();
                break;
            case 4:
                cola.eliminar();
                break;
            case 5:
                cola.cedulaPichincha();
                break;
            case 6:{
                if(cola.estaVacia()){
                    cout<<"La cola esta vacia, registre personas primero."<<endl;
                    break;
                }
                cola.explicarCola();
                break;
            }
            case 7:{
                string cedula = pedirValidado("Ingrese la cedula a modificar: ", Persona::validarCedula);
                string nombre = pedirValidado("Nuevo nombre: ", [](const string& s){ Persona::validarTexto(s, "El nombre"); });
                string apellido = pedirValidado("Nuevo apellido: ", [](const string& s){ Persona::validarTexto(s, "El apellido"); });

                if(!cola.modificar(cedula, nombre, apellido)){
                    cout<<"No se encontro ese numero de cedula"<<endl;
                }
                break;
            }
            case 8:{
                string apellido = pedirValidado("Ingrese el apellido: ", [](const string& s){ Persona::validarTexto(s, "El apellido"); });
                cola.buscarApellido(apellido);
                break;
            }
            case 9:{
                if(cola.estaVacia()){
                    cout<<"La cola esta vacia, registre personas primero."<<endl;
                    break;
                }

                auto mostrarNombreCompleto = [](Persona& p){
                    cout<<p.getNombre()<<" "<<p.getApellido()<<endl;
                };

                cout<<endl<<"NOMBRES COMPLETOS"<<endl;
                Cola.recorrer(mostrarNombreCompleto);
                break;
            }
            case 10:{
                cout<<"SALIENDO.."<<endl;
                return 0;
            }
            default:
                cout<<"Opcion no valida"<<endl;
                break;
            }
        } catch(const invalid_argument& e){
            cout<<"Error de datos: "<<e.what()<<endl;
        } catch(const runtime_error& e){
            cout<<"Aviso: "<<e.what()<<endl;
        } catch(const exception& e){
            cout<<"Error inesperado: "<<e.what()<<endl;
        }
    }while (opcion != 10);

    return 0;
}