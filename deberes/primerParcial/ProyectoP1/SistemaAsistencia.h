#ifndef SISTEMAASISTENCIA_H
#define SISTEMAASISTENCIA_H

#include <string>
#include <map>
#include "ListaDoblementeEnlazada.h"
#include "PersonaProfesor.h"
#include "FranjaHorario.h"
#include "Materia.h"
#include "Registro.h"

struct AperturaClase {
    std::string idMateria;
    std::string fecha;
};

class SistemaAsistencia {
private:
    typedef void (SistemaAsistencia::*Accion)();

    ListaDoblementeEnlazada<PersonaProfesor> profesores;
    ListaDoblementeEnlazada<FranjaHorario>   franjas;
    ListaDoblementeEnlazada<Materia>         materias;
    ListaDoblementeEnlazada<Registro>        registros;

    std::map<std::string, AperturaClase> claseAbierta;
    std::string archivo, archivoProfesores, archivoFranjas, archivoMaterias;
    int horaSimulada;

    int  horaActual() const;
    bool guardarEnArchivo(const Registro& r) const;
    void cargarDatosDemo();
    void cargarArchivo();
    bool cargarCatalogos();
    bool tienePendienteHoy(const std::string& ced);
    bool correoUsado(const std::string& correo, const std::string& cedPropia) const;
    std::string generarCorreo(const std::string& nombre, const std::string& apellido, const std::string& cedPropia) const;
    bool hayConflictoHorario(const std::string& ced, const std::string& idMateriaIgnorar,
                             int ini, int fin, std::string& choque) const;

    template <typename T>
    void menuCrud(const std::string& titulo, const std::string& plural, ListaDoblementeEnlazada<T>& lista,
                  Accion agregar, Accion eliminar, Accion buscar, Accion modificar);

    void agregarProfesor();   void eliminarProfesor();  void buscarProfesor();  void modificarProfesor();
    void agregarMateria();    void eliminarMateria();   void buscarMateria();   void modificarMateria();
    void agregarFranja();     void eliminarFranja();    void buscarFranja();    void modificarFranja();

    void reporteRegistrosProfesor();
    void reporteRegistrosFecha();
    void reporteHorarioProfesor();
    void reporteHorasDictadas();
    void reportePendientes();
    void reporteResumen();
    void exportarCsv();

public:
    SistemaAsistencia(const std::string& arch);

    void iniciar();
    void simularHora();
    void registrarEntrada();
    void registrarSalida();
    void verRegistros() const;
    void menuProfesores();
    void menuMaterias();
    void menuFranjas();
    void menuReportes();
    std::string estadoHora() const;
};

#endif
