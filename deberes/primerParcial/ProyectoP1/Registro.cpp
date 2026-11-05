#include "Registro.h"
#include "Utilidades.h"
#include <iostream>

using namespace std;

Registro::Registro(const string& c, const string& m, char t, int min, const string& f)
    : cedula(c), idMateria(m), tipo(t), minutos(min), fecha(f) {}

string Registro::getCedula() const { return cedula; }
string Registro::getIdMateria() const { return idMateria; }
char Registro::getTipo() const { return tipo; }
string Registro::getFecha() const { return fecha; }
int Registro::getMinutos() const { return minutos; }

string Registro::getId() const {
    return cedula + "#" + idMateria + "#" + string(1, tipo) + "#" + fecha;
}

void Registro::mostrar() const {
    cout << fecha << " " << minutosAHora(minutos) << " | "
         << (tipo == 'E' ? "ENTRADA" : "SALIDA ") << " | Prof: " << cedula
         << " | Materia: " << idMateria << endl;
}

string Registro::serializar() const {
    return cedula + "|" + idMateria + "|" + string(1, tipo) + "|" + to_string(minutos) + "|" + fecha;
}

bool Registro::deserializar(const string& linea, Registro& r) {
    vector<string> c = dividir(linea, '|');
    int min;
    if (c.size() != 5 || c[0].empty() || c[1].empty() || c[4].empty() || (c[2] != "E" && c[2] != "S") ||
        !parsearEntero(c[3], min) || min >= MINUTOS_DIA) return false;
    r = Registro(c[0], c[1], c[2][0], min, c[4]);
    return true;
}
