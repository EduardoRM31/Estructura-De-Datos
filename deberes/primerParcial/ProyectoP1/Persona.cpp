#include "Persona.h"

using namespace std;

Persona::Persona(const string& c, const string& n, const string& a)
    : cedula(c), nombre(n), apellido(a) {}

Persona::~Persona() {}

string Persona::getCedula()   const { return cedula; }
string Persona::getNombre()   const { return nombre; }
string Persona::getApellido() const { return apellido; }
