#pragma once

#include <string>

using namespace std;

class Persona {
private:
    string cedula;
    string nombre;
    string apellido;

public:
    Persona();
    Persona(const string& cedula, const string& nombre, const string& apellido);

    string getCedula() const;
    string getNombre() const;
    string getApellido() const;

    void setCedula(const string& cedula);
    void setNombre(const string& nombre);
    void setApellido(const string& apellido);
    bool validarCedula(const string& cedula);
};