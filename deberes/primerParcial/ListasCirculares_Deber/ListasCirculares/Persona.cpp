#include "Persona.h"

Persona::Persona() {
    this->cedula = "";
    this->nombre = "";
    this->apellido = "";
}

Persona::Persona(const string& cedula, const string& nombre, const string& apellido) {
    this->cedula = cedula;
    this->nombre = nombre;
    this->apellido = apellido;
}

string Persona::getCedula() const {
    return this->cedula;
}

string Persona::getNombre() const {
    return this->nombre;
}

string Persona::getApellido() const {
    return this->apellido;
}

void Persona::setCedula(const string& cedula) {
    this->cedula = cedula;
}

void Persona::setNombre(const string& nombre) {
    this->nombre = nombre;
}

void Persona::setApellido(const string& apellido) {
    this->apellido = apellido;
}

bool Persona::validarCedula(const string& cedula){
     if (cedula.length() != 10) return false;

    int provincia = stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) return false;


    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) { 
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }

    int digitoVerificador = cedula[9] - '0';
    int decenaSuperior = ((suma + 9) / 10) * 10;
    int resultado = decenaSuperior - suma;

    return (resultado == digitoVerificador);
}