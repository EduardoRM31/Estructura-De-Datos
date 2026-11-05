#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include <vector>

const int TOLERANCIA_MIN = 10;
const int MINUTOS_DIA    = 24 * 60;

const int HORA_APERTURA     = 7 * 60;
const int HORA_CIERRE       = 21 * 60;
const int DURACION_FRANJA   = 2 * 60;

const char* const DOMINIO_CORREO = "@espe.edu.ec";

extern bool g_eof;

std::string recortar(const std::string& s);
std::vector<std::string> dividir(const std::string& s, char sep);
std::string aMayusculas(const std::string& s);
bool contieneTexto(const std::string& pajar, const std::string& aguja);
std::string minutosAHora(int m);
bool parsearHora(const std::string& s, int& minutos);
bool parsearEntero(const std::string& s, int& valor);
int  minutosActuales();
std::string fechaActual();
bool dentroDePlazo(int ahora, int objetivo);

bool esCedulaValida(const std::string& s);
bool esIdValido(const std::string& s);
bool esNombreValido(const std::string& s);
bool esTextoValido(const std::string& s);
bool esFechaValida(const std::string& s);
bool esCorreoValido(const std::string& s);
std::string correoUsuario(const std::string& nombre, const std::string& apellido);

bool esFranjaValida(int ini, int fin, std::string& motivo);

const char* const MSG_CEDULA_INVALIDA =
    "Cedula ecuatoriana invalida (10 digitos, provincia 01-24 o 30, tercer digito 0-5 y digito verificador correcto).";

std::string leer(const std::string& mensaje);

bool leerCampo(const std::string& mensaje, bool (*valida)(const std::string&),
               const std::string& error, std::string& destino);

bool leerCampoOpcional(const std::string& mensaje, bool (*valida)(const std::string&),
                       const std::string& error, std::string& destino);
bool leerHora(const std::string& mensaje, int& minutos);
bool confirmar(const std::string& mensaje);

#endif
