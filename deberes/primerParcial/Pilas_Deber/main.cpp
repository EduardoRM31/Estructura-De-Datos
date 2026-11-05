#include <iostream>
#include <string>
#include "Pila.h"
#include "Insertar.h"
#include "Eliminar.h"
#include "Imprimir.h"
#include "Buscar.h"

bool esNumeroValido(const std::string& entrada) {
    if (entrada.empty()) return false;
    for (char c : entrada) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

int main() {
    Pila pila;
    int opcion;
    std::string entrada;

    do {
        std::cout << "\n=================================\n";
        std::cout << "     MENU TDA PILA (PERSONAS)    \n";
        std::cout << "=================================\n";
        std::cout << "1. Insertar Persona (Push)\n";
        std::cout << "2. Eliminar Persona (Pop)\n";
        std::cout << "3. Buscar por Cedula\n";
        std::cout << "4. Imprimir Pila\n";
        std::cout << "5. Ver Total de Personas\n";
        std::cout << "6. Ver Persona en el Tope\n";
        std::cout << "7. Vaciar Pila\n";
        std::cout << "8. Voltear Pila\n";
        std::cout << "9. Ordenar Apellidos por Numero de Caracteres\n";
        std::cout << "10. Salir\n";
        std::cout << "Seleccione una opcion: ";

        std::getline(std::cin, entrada);

        if (!esNumeroValido(entrada)) {
            std::cout << "Error: Debe ingresar un numero valido (no vacio, sin letras ni simbolos).\n";
            continue; // vuelve al menu
        }

        opcion = std::stoi(entrada);

        switch (opcion) {
            case 1: {
                Insertar operacionInsertar(pila);
                operacionInsertar.ejecutar();
                break;
            }
            case 2: {
                Eliminar operacionEliminar(pila);
                operacionEliminar.ejecutar();
                break;
            }
            case 3: {
                Buscar operacionBuscar(pila);
                operacionBuscar.ejecutar();
                break;
            }
            case 4: {
                Imprimir operacionImprimir(pila);
                operacionImprimir.ejecutar();
                break;
            }
            case 5:
                std::cout << "Total de elementos en la pila: " << pila.contarElementos() << "\n";
                break;
            case 6:
                pila.verTope();
                break;
            case 7:
                pila.vaciarPila();
                break;
            case 8:
                pila.voltearPila();
                break;
            case 9:
                pila.mostrarApellidosOrdenados();
                break;
            case 10:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 10);

    return 0;
}
