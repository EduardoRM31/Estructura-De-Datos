#include "Persona.h"
#include <iostream>

Persona::Persona() : nombre(""), cedula(""), apellido("") {}

Persona::Persona(const std::string& nombre, const std::string& cedula, const std::string& apellido) {
    this->nombre = nombre;
    this->cedula = cedula;
    this->apellido = apellido;
}

std::string Persona::getNombre() const { return nombre; }
std::string Persona::getApellido() const { return apellido; }
std::string Persona::getCedula() const { return cedula; }

void Persona::setNombre(const std::string& newNombre) { nombre = newNombre; }
void Persona::setApellido(const std::string& newApellido) { apellido = newApellido; }
void Persona::setCedula(const std::string& newCedula) { cedula = newCedula; }

void Persona::mostrar() const {
    std::cout << "Nombre: " << nombre << " | Apellido: " << apellido << " | Cedula: " << cedula << "\n";
}

// 
bool Persona::esCedulaValidaEcuador(const std::string& cedula) {
    if (cedula.length() != 10) return false;

    for (char c : cedula) {
        if (c < '0' || c > '9') return false;
    }

    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) return false;

    // 1. Usamos .at(2) en lugar de cedula[2]
    int tercerDigito = cedula.at(2) - '0';
    if (tercerDigito >= 6) return false;

    int suma = 0;
    for (int i = 0; i < 9; i++) {

        int dig = cedula.at(i) - '0';
        if (i % 2 == 0) { // posiciones pares (0, 2, 4, 6, 8)
            dig *= 2;
            if (dig > 9) dig -= 9;
        }
        suma += dig;
    }

    int verificador = (10 - (suma % 10)) % 10;


    return verificador == (cedula.at(9) - '0');
}
