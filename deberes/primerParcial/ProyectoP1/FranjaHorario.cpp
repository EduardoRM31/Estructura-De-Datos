#include "FranjaHorario.h"
#include "Utilidades.h"
#include <iostream>

using namespace std;

FranjaHorario::FranjaHorario(const string& id, int ini, int fin)
    : idHorario(id), horaInicioMinutos(ini), horaFinMinutos(fin) {}

string FranjaHorario::getIdHorario() const { return idHorario; }
int FranjaHorario::getHoraInicioMinutos() const { return horaInicioMinutos; }
int FranjaHorario::getHoraFinMinutos() const { return horaFinMinutos; }

string FranjaHorario::getId() const { return idHorario; }

void FranjaHorario::mostrar() const {
    cout << "Franja " << idHorario << ": " << minutosAHora(horaInicioMinutos)
         << " - " << minutosAHora(horaFinMinutos)
         << "  (" << horaInicioMinutos << " - " << horaFinMinutos << " min)" << endl;
}

void FranjaHorario::setHoras(int ini, int fin) { horaInicioMinutos = ini; horaFinMinutos = fin; }

string FranjaHorario::serializar() const {
    return idHorario + "|" + to_string(horaInicioMinutos) + "|" + to_string(horaFinMinutos);
}

bool FranjaHorario::deserializar(const string& linea, FranjaHorario& f) {
    vector<string> c = dividir(linea, '|');
    if (c.size() != 3) return false;
    int ini, fin;
    string motivo;
    if (!esIdValido(c[0]) || !parsearEntero(c[1], ini) || !parsearEntero(c[2], fin)) return false;
    if (!esFranjaValida(ini, fin, motivo)) return false;
    f = FranjaHorario(aMayusculas(c[0]), ini, fin);
    return true;
}
