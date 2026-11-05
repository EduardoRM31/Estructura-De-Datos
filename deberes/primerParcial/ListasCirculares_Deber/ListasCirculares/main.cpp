#include <iostream>
#include <string>
#include "Nodo.h"
#include "Persona.h"

using namespace std;

int main() {
    Nodo* cabeza = nullptr;
    int opcion;
    string cedula, nombre, apellido;

    do {
        cout << "\n========================================\n";
        cout << "      LISTA DOBLEMENTE CIRCULAR         \n";
        cout << "========================================\n";
        cout << "1. Insertar persona\n";
        cout << "2. Buscar por cedula\n";
        cout << "3. Modificar persona\n";
        cout << "4. Eliminar persona\n";
        cout << "5. Mostrar lista (Adelante)\n";
        cout << "6. Mostrar lista (Reverso)\n";
        cout << "7. Contar nodos (Total)\n";
        cout << "8. Contiene cedula\n";
        cout << "9. Salir\n";
        cout << "========================================\n";
        cout << "Seleccione una opcion: ";

        // Validación por si ingresan letras en lugar de números
        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Por favor, ingrese un numero.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (opcion) {
            case 1: {
                cout << "\n--- INSERTAR PERSONA ---\n";
                cout << "Ingrese cedula: ";
                cin >> cedula;

                // Opcional: Validar la cédula usando el método de Persona
                Persona pValidador;
                if (!pValidador.validarCedula(cedula)) {
                    cout << "¡Atencion! La cedula ingresada no es valida segun el algoritmo ecuatoriano.\n";
                    // Si prefieres que no se inserte si es falsa, descomenta el siguiente 'break':
                    // break;
                }

                cout << "Ingrese nombre: ";
                cin >> ws; // Limpia el buffer
                getline(cin, nombre);
                cout << "Ingrese apellido: ";
                getline(cin, apellido);

                Nodo::insertar(cabeza, cedula, nombre, apellido);
                break;
            }
            case 2: {
                cout << "\n--- BUSCAR POR CEDULA ---\n";
                cout << "Ingrese la cedula a buscar: ";
                cin >> cedula;
                Nodo::buscarPorCedula(cabeza, cedula);
                break;
            }
            case 3: {
                cout << "\n--- MODIFICAR PERSONA ---\n";
                cout << "Ingrese la cedula de la persona a modificar: ";
                cin >> cedula;
                Nodo::modificar(cabeza, cedula);
                break;
            }
            case 4: {
                cout << "\n--- ELIMINAR PERSONA ---\n";
                cout << "Ingrese la cedula a eliminar: ";
                cin >> cedula;
                
                if (cabeza != nullptr) {
                    // La cola en una lista circular es el nodo anterior a la cabeza
                    Nodo* cola = cabeza->getAnterior();
                    Nodo::eliminar(cabeza, cola, cedula);
                } else {
                    cout << "La lista esta vacia. No hay elementos para eliminar.\n";
                }
                break;
            }
            case 5: {
                cout << "\n--- LISTA DE PERSONAS (ADELANTE) ---\n";
                if (cabeza != nullptr) {
                    cabeza->Imprimir(cabeza);
                } else {
                    cout << "La lista esta vacia.\n";
                }
                break;
            }
            case 6: {
                cout << "\n--- LISTA DE PERSONAS (REVERSO) ---\n";
                if (cabeza != nullptr) {
                    cabeza->ImprimirReverso(cabeza);
                } else {
                    cout << "La lista esta vacia.\n";
                }
                break;
            }
            case 7: {
                cout << "\n--- TOTAL DE NODOS ---\n";
                int total = Nodo::contarNodos(cabeza);
                cout << "Actualmente hay " << total << " persona(s) registrada(s).\n";
                break;
            }
            case 8:{
                cout << "\n--- CONTIENE CEDULA ---\n";
                cout << "Ingrese la cedula a verificar: ";
                cin >> cedula;

                bool existe = Nodo::contiene(cabeza, cedula);
                cout << "Resultado: " << (existe ? "true" : "false") << endl;
                break;
            }
            case 9:
                cout << "\nSaliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                cout << "\nOpcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 9);

    return 0;
}