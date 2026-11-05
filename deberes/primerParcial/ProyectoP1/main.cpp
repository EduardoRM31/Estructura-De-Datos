#include <iostream>
#include <string>
#include <exception>
#include "SistemaAsistencia.h"
#include "Utilidades.h"

using namespace std;

int main() {
    try {
        SistemaAsistencia sistema("asistencia.txt");
        sistema.iniciar();

        int opcion = -1;
        while (opcion != 0 && !g_eof) {
            try {
                cout << "\n===== CONTROL DE ASISTENCIA (" << sistema.estadoHora() << ") =====" << endl;
                cout << "1. Registrar entrada\n2. Registrar salida\n3. Ver registros\n"
                        "4. Menu profesores\n5. Menu materias\n6. Menu franjas\n"
                        "7. Simular hora\n8. Reportes\n0. Salir" << endl;
                string texto = leer("Opcion: ");
                if (g_eof) break;
                if (!parsearEntero(texto, opcion)) { cout << "Opcion invalida." << endl; opcion = -1; continue; }

                switch (opcion) {
                    case 1: sistema.registrarEntrada(); break;
                    case 2: sistema.registrarSalida();  break;
                    case 3: sistema.verRegistros();     break;
                    case 4: sistema.menuProfesores();   break;
                    case 5: sistema.menuMaterias();     break;
                    case 6: sistema.menuFranjas();      break;
                    case 7: sistema.simularHora();      break;
                    case 8: sistema.menuReportes();     break;
                    case 0: cout << "Hasta luego." << endl; break;
                    default: cout << "Opcion invalida." << endl;
                }
            } catch (const exception& e) {
                cout << "ERROR controlado: " << e.what() << ". El programa continua." << endl;
                opcion = -1;
            } catch (...) {
                cout << "ERROR controlado. El programa continua." << endl;
                opcion = -1;
            }
        }
        return 0;
    } catch (...) {
        cout << "ERROR fatal controlado. Los registros ya guardados no se pierden." << endl;
        return 1;
    }
}
