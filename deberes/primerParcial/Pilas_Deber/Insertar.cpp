#include "Insertar.h"
#include "Persona.h"
#include <iostream>
#include <string>
#include <conio.h>

// Captura solo numeros y los muestra en pantalla
std::string leerSoloNumeros(int longitud) {
    std::string entrada = "";
    char c;
    while (entrada.size() < longitud) {
        c = getch();
        if (c >= '0' && c <= '9') {
            std::cout << c;
            entrada += c;
        }
    }
    std::cout << std::endl;
    return entrada;
}

Insertar::Insertar(Pila& p) : pila(p) {}

std::string Insertar::ingresarLetras() {   // nota el Insertar::
    std::string texto = "";
    char tecla;

    do {
        tecla = getch();
        if ((tecla >= 'A' && tecla <= 'Z') || (tecla >= 'a' && tecla <= 'z') || tecla == ' ') {
            texto += tecla;
            std::cout << tecla;
        }
        else if (tecla == 8 && !texto.empty()) { // retroceso
            texto.erase(texto.size() - 1);
            std::cout << "\b \b";
        }
    } while (tecla != 13); // Enter

    std::cout << std::endl;
    return texto;
}

void Insertar::ejecutar() {
    std::string nombre, apellido, cedula;

    // Nombre
    do {
        std::cout << "Ingrese Nombre: ";
        nombre = ingresarLetras();
        if (nombre.empty()) {
            std::cout << "Error: El nombre no puede estar vacio.\n";
        }
    } while (nombre.empty());

    // Apellido
    do {
        std::cout << "Ingrese Apellido: ";
        apellido = ingresarLetras();
        if (apellido.empty()) {
            std::cout << "Error: El apellido no puede estar vacio.\n";
        }
    } while (apellido.empty());

    // Cedula
    do {
        std::cout << "Ingrese Cedula ecuatoriana (10 digitos): ";
        cedula = leerSoloNumeros(10);

        if (!Persona::esCedulaValidaEcuador(cedula)) {
            std::cout << "\nError: Cedula ecuatoriana invalida. Intente de nuevo.\n";
        }
    } while (!Persona::esCedulaValidaEcuador(cedula));

    Persona nueva(nombre, cedula, apellido);
    pila.push(nueva);
}
