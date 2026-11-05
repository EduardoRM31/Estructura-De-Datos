#include "PersonaProfesor.h"
#include "Utilidades.h"
#include <iostream>

using namespace std;

PersonaProfesor::PersonaProfesor(const string& c, const string& n, const string& a, const string& co)
    : Persona(c, n, a), correo(co) {}

void PersonaProfesor::mostrarDatos() const {
    cout << "Cedula: " << cedula << " | " << nombre << " " << apellido << " | Correo: " << correo << endl;
}

string PersonaProfesor::getId() const { return cedula; }
void PersonaProfesor::mostrar() const { mostrarDatos(); }

void PersonaProfesor::setNombre(const string& n)   { nombre = n; }
void PersonaProfesor::setApellido(const string& a) { apellido = a; }
string PersonaProfesor::getCorreo() const { return correo; }
void PersonaProfesor::setCorreo(const string& c) { correo = c; }

string PersonaProfesor::serializar() const { return cedula + "|" + nombre + "|" + apellido + "|" + correo; }

bool PersonaProfesor::deserializar(const string& linea, PersonaProfesor& p) {
    vector<string> c = dividir(linea, '|');
    if (c.size() != 3 && c.size() != 4) return false;
    if (!esCedulaValida(c[0]) || !esNombreValido(c[1]) || !esNombreValido(c[2])) return false;
    p = PersonaProfesor(c[0], c[1], c[2], c.size() == 4 ? c[3] : "");
    return true;
}
