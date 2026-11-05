#include "Materia.h"
#include "Utilidades.h"
#include <iostream>

using namespace std;

Materia::Materia(const string& id, const string& nombre, const string& idHorario,
                 const string& cedProf)
    : idMateria(id), nombreMateria(nombre), idHorarioAsociado(idHorario),
      cedulaProfesor(cedProf) {}

string Materia::getIdMateria() const { return idMateria; }
string Materia::getNombreMateria() const { return nombreMateria; }
string Materia::getIdHorarioAsociado() const { return idHorarioAsociado; }
string Materia::getCedulaProfesor() const { return cedulaProfesor; }

string Materia::getId() const { return idMateria; }

void Materia::mostrar() const {
    cout << idMateria << " - " << nombreMateria << " | Franja: " << idHorarioAsociado
         << " | Profesor: " << cedulaProfesor << endl;
}

void Materia::setNombreMateria(const string& n)      { nombreMateria = n; }
void Materia::setIdHorarioAsociado(const string& id) { idHorarioAsociado = id; }
void Materia::setCedulaProfesor(const string& ced)   { cedulaProfesor = ced; }

string Materia::serializar() const {
    return idMateria + "|" + nombreMateria + "|" + idHorarioAsociado + "|" + cedulaProfesor;
}

bool Materia::deserializar(const string& linea, Materia& m) {
    vector<string> c = dividir(linea, '|');
    if (c.size() != 4) return false;
    if (!esIdValido(c[0]) || !esTextoValido(c[1]) || !esIdValido(c[2]) || !esCedulaValida(c[3])) return false;
    m = Materia(aMayusculas(c[0]), c[1], aMayusculas(c[2]), c[3]);
    return true;
}
