#include "SistemaAsistencia.h"
#include "Utilidades.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

namespace {

void cancelar() { cout << "Cancelado." << endl; }

string duracion(int minutos) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%dh %02dmin", minutos / 60, minutos % 60);
    return string(buf);
}

string campoCsv(const string& s) {
    if (s.find_first_of(";\"\n") == string::npos) return s;
    string r = "\"";
    for (size_t i = 0; i < s.size(); i++) r += (s[i] == '"') ? string("\"\"") : string(1, s[i]);
    return r + "\"";
}

template <typename T>
void guardar(const ListaDoblementeEnlazada<T>& lista, const string& ruta) {
    ofstream out(ruta.c_str(), ios::trunc);
    lista.paraCada([&](const T& x) { out << x.serializar() << "\n"; });
    out.flush();
    if (!out.good())
        cout << "AVISO: no se pudo escribir " << ruta << ". Este cambio solo vale hasta cerrar el programa." << endl;
}

template <typename T, typename F>
void cargar(ifstream& in, ListaDoblementeEnlazada<T>& lista, int& omitidos, F aceptar) {
    string linea;
    while (getline(in, linea)) {
        linea = recortar(linea);
        if (linea.empty()) continue;
        T x;
        if (T::deserializar(linea, x) && lista.buscar(x.getId()) == nullptr && aceptar(x)) lista.agregar(x);
        else omitidos++;
    }
}

template <typename T>
T* pedir(ListaDoblementeEnlazada<T>& lista, const string& mensaje, bool (*valida)(const string&),
         const string& error, const string& noExiste) {
    cout << "(ENTER vacio = cancelar)" << endl;
    string id;
    if (!leerCampo(mensaje, valida, error, id)) { cancelar(); return nullptr; }
    T* x = lista.buscar(aMayusculas(id));
    if (x == nullptr) cout << noExiste << endl;
    return x;
}

template <typename T, typename F>
void buscarEn(const ListaDoblementeEnlazada<T>& lista, const string& mensaje, F coincide) {
    string t = leer(mensaje);
    if (g_eof || t.empty()) return cancelar();
    int n = 0;
    lista.paraCada([&](const T& x) { if (coincide(x, t)) { cout << "  "; x.mostrar(); n++; } });
    if (n == 0) cout << "Sin coincidencias." << endl;
    else        cout << n << " coincidencia(s)." << endl;
}

template <typename F>
void listarRegistros(const ListaDoblementeEnlazada<Registro>& registros, const string& titulo, F filtro) {
    cout << titulo << endl;
    int n = 0;
    registros.paraCada([&](const Registro& r) { if (filtro(r)) { cout << "  "; r.mostrar(); n++; } });
    if (n == 0) cout << "  (sin registros)" << endl;
    else        cout << n << " registro(s)." << endl;
}

const char* const ERR_PROFESOR = "ERROR: no existe un profesor con esa cedula.";
const char* const ERR_NOMBRE   = "Nombre invalido: solo letras, espacios, - y ' (max 40).";
const char* const ERR_APELLIDO = "Apellido invalido: solo letras, espacios, - y ' (max 40).";
const char* const ERR_ID       = "ID invalido: 1 a 10 letras/numeros, sin espacios ni simbolos.";

}

SistemaAsistencia::SistemaAsistencia(const string& arch)
    : archivo(arch), archivoProfesores("profesores.txt"), archivoFranjas("franjas.txt"),
      archivoMaterias("materias.txt"), horaSimulada(-1) {}

int SistemaAsistencia::horaActual() const {
    return horaSimulada >= 0 ? horaSimulada : minutosActuales();
}

string SistemaAsistencia::estadoHora() const {
    return horaSimulada >= 0 ? "SIMULADA " + minutosAHora(horaSimulada) : string("hora real");
}

bool SistemaAsistencia::guardarEnArchivo(const Registro& r) const {
    ofstream out(archivo.c_str(), ios::app);
    out << r.serializar() << "\n";
    out.flush();
    return out.good();
}

void SistemaAsistencia::cargarDatosDemo() {
    franjas.agregar(FranjaHorario("H1", 7 * 60, 9 * 60));
    franjas.agregar(FranjaHorario("H2", 9 * 60, 11 * 60));
    franjas.agregar(FranjaHorario("H3", 14 * 60, 16 * 60));

    profesores.agregar(PersonaProfesor("1712345675", "Carlos", "Mena", generarCorreo("Carlos", "Mena", "1712345675")));
    profesores.agregar(PersonaProfesor("1719876540", "Ana", "Torres", generarCorreo("Ana", "Torres", "1719876540")));

    materias.agregar(Materia("M01", "Estructura de Datos", "H1", "1712345675"));
    materias.agregar(Materia("M02", "Programacion Orientada a Objetos", "H2", "1712345675"));
    materias.agregar(Materia("M03", "Redes", "H1", "1719876540"));
}

bool SistemaAsistencia::cargarCatalogos() {
    ifstream fFr(archivoFranjas.c_str()), fPr(archivoProfesores.c_str()), fMa(archivoMaterias.c_str());
    if (!fFr && !fPr && !fMa) return false;

    int omitidos = 0;
    bool correosNuevos = false;
    cargar(fFr, franjas, omitidos, [](const FranjaHorario&) { return true; });
    cargar(fPr, profesores, omitidos, [&](PersonaProfesor& p) {
        if (!esCorreoValido(p.getCorreo()) || correoUsado(p.getCorreo(), p.getCedula())) {
            p.setCorreo(generarCorreo(p.getNombre(), p.getApellido(), p.getCedula()));
            correosNuevos = true;
        }
        return true;
    });
    if (correosNuevos) guardar(profesores, archivoProfesores);
    cargar(fMa, materias, omitidos, [&](const Materia& m) {
        return franjas.buscar(m.getIdHorarioAsociado()) != nullptr &&
               profesores.buscar(m.getCedulaProfesor()) != nullptr;
    });

    cout << "Datos cargados: " << profesores.getTamano() << " profesores, "
         << materias.getTamano() << " materias, " << franjas.getTamano() << " franjas";
    if (omitidos > 0) cout << " (" << omitidos << " lineas invalidas omitidas)";
    cout << endl;
    return true;
}

void SistemaAsistencia::cargarArchivo() {
    ifstream in(archivo.c_str());
    if (!in.is_open()) {
        ofstream nuevo(archivo.c_str(), ios::app);
        if (nuevo.is_open()) cout << "Archivo " << archivo << " no existia: se creo uno nuevo." << endl;
        else cout << "AVISO: no se pudo crear " << archivo << ". Los registros no se podran guardar." << endl;
        return;
    }
    string linea;
    int cargados = 0, omitidos = 0;
    while (getline(in, linea)) {
        linea = recortar(linea);
        if (linea.empty()) continue;
        Registro r;
        if (!Registro::deserializar(linea, r)) { omitidos++; continue; }
        registros.agregar(r);
        if (r.getTipo() == 'E') {
            AperturaClase a;
            a.idMateria = r.getIdMateria();
            a.fecha = r.getFecha();
            claseAbierta[r.getCedula()] = a;
        } else {
            claseAbierta.erase(r.getCedula());
        }
        cargados++;
    }
    cout << "Archivo cargado: " << cargados << " registros";
    if (omitidos > 0) cout << " (" << omitidos << " lineas corruptas omitidas)";
    cout << endl;
}

void SistemaAsistencia::iniciar() {
    if (!cargarCatalogos()) {
        cargarDatosDemo();
        guardar(franjas, archivoFranjas);
        guardar(profesores, archivoProfesores);
        guardar(materias, archivoMaterias);
        cout << "Primera ejecucion: se cargaron datos de ejemplo y se crearon " << archivoProfesores
             << ", " << archivoFranjas << " y " << archivoMaterias << "." << endl;
    }
    cargarArchivo();
}

void SistemaAsistencia::simularHora() {
    string s = leer("Hora simulada HH:MM (ENTER = volver a la hora real): ");
    if (s.empty()) { horaSimulada = -1; cout << "Usando hora real del sistema." << endl; return; }
    int m;
    if (!parsearHora(s, m)) { cout << "Formato invalido. Ejemplo: 07:05" << endl; return; }
    horaSimulada = m;
    cout << "Hora simulada: " << minutosAHora(m) << endl;
}

bool SistemaAsistencia::tienePendienteHoy(const string& ced) {
    auto it = claseAbierta.find(ced);
    if (it == claseAbierta.end()) return false;
    if (it->second.fecha != fechaActual()) { claseAbierta.erase(it); return false; }
    return true;
}

bool SistemaAsistencia::correoUsado(const string& correo, const string& cedPropia) const {
    bool usado = false;
    profesores.paraCada([&](const PersonaProfesor& p) {
        if (p.getCedula() != cedPropia && p.getCorreo() == correo) usado = true;
    });
    return usado;
}

string SistemaAsistencia::generarCorreo(const string& nombre, const string& apellido, const string& cedPropia) const {
    string base = correoUsuario(nombre, apellido);
    for (int n = 0;; n++) {
        string correo = base + (n == 0 ? "" : to_string(n)) + DOMINIO_CORREO;
        if (!correoUsado(correo, cedPropia)) return correo;
    }
}

bool SistemaAsistencia::hayConflictoHorario(const string& ced, const string& idMateriaIgnorar,
                                            int ini, int fin, string& choque) const {
    choque.clear();
    materias.paraCada([&](const Materia& m) {
        if (m.getCedulaProfesor() != ced || m.getIdMateria() == idMateriaIgnorar) return;
        const FranjaHorario* f = franjas.buscar(m.getIdHorarioAsociado());
        if (f != nullptr && f->getHoraInicioMinutos() < fin && ini < f->getHoraFinMinutos())
            choque = m.getIdMateria();
    });
    return !choque.empty();
}

void SistemaAsistencia::registrarEntrada() {
    string ced = leer("Cedula del profesor: ");
    if (g_eof) return;
    if (!esCedulaValida(ced)) { cout << "DENEGADO: " << MSG_CEDULA_INVALIDA << endl; return; }
    if (profesores.buscar(ced) == nullptr) { cout << "DENEGADO: no existe un profesor con esa cedula." << endl; return; }

    string idMat = aMayusculas(leer("ID de la materia (ej. M01): "));
    if (g_eof) return;
    if (!esIdValido(idMat)) { cout << "DENEGADO: ID de materia invalido." << endl; return; }
    Materia* mat = materias.buscar(idMat);
    if (mat == nullptr) { cout << "DENEGADO: la materia no existe." << endl; return; }
    if (mat->getCedulaProfesor() != ced) {
        cout << "DENEGADO: esa materia no esta asignada a este profesor." << endl; return;
    }

    auto it = claseAbierta.find(ced);
    if (it != claseAbierta.end()) {
        if (it->second.fecha == fechaActual()) {
            cout << "DENEGADO: no registro la SALIDA de la materia " << it->second.idMateria
                 << "; no puede registrar la entrada de otra materia.";
            Materia* pend = materias.buscar(it->second.idMateria);
            FranjaHorario* fp = (pend != nullptr) ? franjas.buscar(pend->getIdHorarioAsociado()) : nullptr;
            if (fp != nullptr) {
                int limite = fp->getHoraFinMinutos() + TOLERANCIA_MIN;
                if (horaActual() <= limite) cout << " Registre la salida hasta las " << minutosAHora(limite) << ".";
                else                        cout << " El plazo para registrarla vencio a las " << minutosAHora(limite) << ".";
            }
            cout << endl; return;
        }
        cout << "AVISO: la entrada de " << it->second.idMateria << " del " << it->second.fecha
             << " quedo sin salida y ya no es valida." << endl;
        claseAbierta.erase(it);
    }

    FranjaHorario* fr = franjas.buscar(mat->getIdHorarioAsociado());
    if (fr == nullptr) { cout << "DENEGADO: la materia tiene una franja inexistente." << endl; return; }

    int ahora = horaActual();
    int ini = fr->getHoraInicioMinutos();
    if (!dentroDePlazo(ahora, ini)) {
        cout << "DENEGADO: son las " << minutosAHora(ahora) << ". La entrada de " << idMat
             << " solo se permite entre " << minutosAHora(ini - TOLERANCIA_MIN) << " y "
             << minutosAHora(ini + TOLERANCIA_MIN) << " (10 minutos antes o despues del inicio)." << endl; return;
    }

    Registro r(ced, idMat, 'E', ahora, fechaActual());
    if (registros.buscar(r.getId()) != nullptr) {
        cout << "DENEGADO: la entrada de esta materia ya fue registrada hoy." << endl; return;
    }
    if (!guardarEnArchivo(r)) {
        cout << "ERROR: no se pudo escribir " << archivo << ". Registro cancelado." << endl; return;
    }

    registros.agregar(r);
    AperturaClase a;
    a.idMateria = idMat;
    a.fecha = r.getFecha();
    claseAbierta[ced] = a;
    cout << "OK: entrada registrada a las " << minutosAHora(ahora) << " (" << mat->getNombreMateria() << ")." << endl;
}

void SistemaAsistencia::registrarSalida() {
    string ced = leer("Cedula del profesor: ");
    if (g_eof) return;
    if (!esCedulaValida(ced)) { cout << "DENEGADO: " << MSG_CEDULA_INVALIDA << endl; return; }
    if (profesores.buscar(ced) == nullptr) { cout << "DENEGADO: no existe un profesor con esa cedula." << endl; return; }

    auto it = claseAbierta.find(ced);
    if (it == claseAbierta.end()) {
        cout << "DENEGADO: no tiene ninguna entrada pendiente de salida." << endl; return;
    }
    if (it->second.fecha != fechaActual()) {
        cout << "DENEGADO: la entrada pendiente (" << it->second.idMateria << ") es del "
             << it->second.fecha << " y ya expiro. Registre una nueva entrada." << endl;
        claseAbierta.erase(it);
        return;
    }
    string idMat = it->second.idMateria;
    Materia* mat = materias.buscar(idMat);
    FranjaHorario* fr = (mat != nullptr) ? franjas.buscar(mat->getIdHorarioAsociado()) : nullptr;
    if (fr == nullptr) { cout << "DENEGADO: datos de materia/franja inconsistentes." << endl; return; }

    int ahora = horaActual();
    int fin = fr->getHoraFinMinutos();
    if (!dentroDePlazo(ahora, fin)) {
        cout << "DENEGADO: son las " << minutosAHora(ahora) << ". La salida de " << idMat
             << " solo se permite entre " << minutosAHora(fin - TOLERANCIA_MIN) << " y "
             << minutosAHora(fin + TOLERANCIA_MIN) << " (10 minutos antes o despues del fin)." << endl;
        if (ahora > fin + TOLERANCIA_MIN)
            cout << "El plazo vencio: mientras esta salida siga sin registrarse no podra registrar entradas de otras materias hoy." << endl;
        return;
    }

    Registro r(ced, idMat, 'S', ahora, fechaActual());
    if (!guardarEnArchivo(r)) {
        cout << "ERROR: no se pudo escribir " << archivo << ". Registro cancelado." << endl; return;
    }

    registros.agregar(r);
    claseAbierta.erase(ced);
    cout << "OK: salida registrada a las " << minutosAHora(ahora) << " (" << mat->getNombreMateria() << ")." << endl;
}

void SistemaAsistencia::verRegistros() const {
    cout << "--- Registros ---" << endl;
    registros.imprimir();
}

template <typename T>
void SistemaAsistencia::menuCrud(const string& titulo, const string& plural, ListaDoblementeEnlazada<T>& lista,
                                 Accion agregar, Accion eliminar, Accion buscar, Accion modificar) {
    const Accion acciones[] = { nullptr, agregar, eliminar, buscar, nullptr, modificar };
    while (!g_eof) {
        cout << "\n--- " << titulo << " ---" << endl;
        cout << "1. Agregar\n2. Eliminar\n3. Buscar\n4. Imprimir todos\n5. Modificar\n0. Volver" << endl;
        string t = leer("Opcion: ");
        if (g_eof) return;
        int op;
        if (!parsearEntero(t, op) || op > 5) { cout << "Opcion invalida." << endl; continue; }
        if (op == 0) return;
        if (op == 4) { cout << "--- " << plural << " ---" << endl; lista.imprimir(); }
        else         (this->*acciones[op])();
    }
}

void SistemaAsistencia::menuProfesores() {
    menuCrud("MENU PROFESORES", "Profesores", profesores, &SistemaAsistencia::agregarProfesor,
             &SistemaAsistencia::eliminarProfesor, &SistemaAsistencia::buscarProfesor, &SistemaAsistencia::modificarProfesor);
}

void SistemaAsistencia::menuMaterias() {
    menuCrud("MENU MATERIAS", "Materias", materias, &SistemaAsistencia::agregarMateria,
             &SistemaAsistencia::eliminarMateria, &SistemaAsistencia::buscarMateria, &SistemaAsistencia::modificarMateria);
}

void SistemaAsistencia::menuFranjas() {
    menuCrud("MENU FRANJAS", "Franjas", franjas, &SistemaAsistencia::agregarFranja,
             &SistemaAsistencia::eliminarFranja, &SistemaAsistencia::buscarFranja, &SistemaAsistencia::modificarFranja);
}

void SistemaAsistencia::agregarProfesor() {
    cout << "(ENTER vacio = cancelar)" << endl;
    string ced, nom, ape;
    if (!leerCampo("Cedula (10 digitos): ", esCedulaValida, MSG_CEDULA_INVALIDA, ced)) return cancelar();
    if (profesores.buscar(ced) != nullptr) { cout << "ERROR: ya existe un profesor con esa cedula." << endl; return; }
    if (!leerCampo("Nombre: ", esNombreValido, ERR_NOMBRE, nom)) return cancelar();
    if (!leerCampo("Apellido: ", esNombreValido, ERR_APELLIDO, ape)) return cancelar();
    string correo = generarCorreo(nom, ape, ced);
    profesores.agregar(PersonaProfesor(ced, nom, ape, correo));
    guardar(profesores, archivoProfesores);
    cout << "OK: profesor agregado. Correo: " << correo << endl;
}

void SistemaAsistencia::eliminarProfesor() {
    PersonaProfesor* p = pedir(profesores, "Cedula del profesor a eliminar: ", esCedulaValida, MSG_CEDULA_INVALIDA, ERR_PROFESOR);
    if (p == nullptr) return;
    string ced = p->getCedula();

    if (tienePendienteHoy(ced)) {
        cout << "DENEGADO: el profesor tiene una entrada sin salida; registre primero su salida." << endl; return;
    }
    int nMaterias = 0;
    materias.paraCada([&](const Materia& m) { if (m.getCedulaProfesor() == ced) nMaterias++; });
    if (nMaterias > 0) {
        cout << "DENEGADO: el profesor tiene " << nMaterias
             << " materia(s) asignada(s). Elimine esas materias primero." << endl; return;
    }
    cout << "Se eliminara: "; p->mostrar();
    if (!confirmar("Confirma")) return cancelar();
    profesores.eliminar(ced);
    guardar(profesores, archivoProfesores);
    cout << "OK: profesor eliminado." << endl;
}

void SistemaAsistencia::buscarProfesor() {
    buscarEn(profesores, "Buscar (cedula, nombre, apellido o correo): ", [](const PersonaProfesor& p, const string& t) {
        return contieneTexto(p.getCedula(), t) || contieneTexto(p.getNombre(), t) ||
               contieneTexto(p.getApellido(), t) || contieneTexto(p.getCorreo(), t);
    });
}

void SistemaAsistencia::modificarProfesor() {
    PersonaProfesor* p = pedir(profesores, "Cedula del profesor a modificar: ", esCedulaValida, MSG_CEDULA_INVALIDA, ERR_PROFESOR);
    if (p == nullptr) return;

    cout << "Actual: "; p->mostrar();
    cout << "(ENTER vacio = conservar el dato actual; la cedula no se puede cambiar)" << endl;
    string nom = p->getNombre(), ape = p->getApellido();
    leerCampoOpcional("Nuevo nombre: ", esNombreValido, ERR_NOMBRE, nom);
    if (g_eof) return cancelar();
    leerCampoOpcional("Nuevo apellido: ", esNombreValido, ERR_APELLIDO, ape);
    if (g_eof) return cancelar();

    if (nom == p->getNombre() && ape == p->getApellido()) { cout << "Sin cambios." << endl; return; }
    p->setNombre(nom);
    p->setApellido(ape);
    p->setCorreo(generarCorreo(nom, ape, p->getCedula()));
    guardar(profesores, archivoProfesores);
    cout << "OK: profesor modificado: "; p->mostrar();
}

void SistemaAsistencia::agregarFranja() {
    cout << "(ENTER vacio = cancelar)" << endl;
    string id;
    int ini = 0, fin = 0;
    if (!leerCampo("ID de la franja (ej. H4): ", esIdValido, ERR_ID, id)) return cancelar();
    id = aMayusculas(id);
    if (franjas.buscar(id) != nullptr) { cout << "ERROR: ya existe una franja con ese ID." << endl; return; }
    cout << "Las franjas duran exactamente 2 horas y van entre " << minutosAHora(HORA_APERTURA)
         << " y " << minutosAHora(HORA_CIERRE) << "." << endl;
    string motivo;

    while (true) {
        if (!leerHora("Hora de inicio (HH:MM): ", ini)) return cancelar();
        if (esFranjaValida(ini, ini + DURACION_FRANJA, motivo)) break;
        cout << "  Inicio invalido: " << motivo << " (ENTER vacio = cancelar)" << endl;
    }
    while (true) {
        if (!leerHora("Hora de fin (HH:MM): ", fin)) return cancelar();
        if (esFranjaValida(ini, fin, motivo)) break;
        cout << "  Fin invalido: " << motivo << " Con inicio " << minutosAHora(ini)
             << " el fin debe ser " << minutosAHora(ini + DURACION_FRANJA) << ". (ENTER vacio = cancelar)" << endl;
    }
    franjas.agregar(FranjaHorario(id, ini, fin));
    guardar(franjas, archivoFranjas);
    cout << "OK: franja agregada." << endl;
}

void SistemaAsistencia::eliminarFranja() {
    FranjaHorario* f = pedir(franjas, "ID de la franja a eliminar: ", esIdValido, "ID invalido.", "ERROR: no existe esa franja.");
    if (f == nullptr) return;
    string id = f->getId();

    int nMaterias = 0;
    materias.paraCada([&](const Materia& m) { if (m.getIdHorarioAsociado() == id) nMaterias++; });
    if (nMaterias > 0) {
        cout << "DENEGADO: " << nMaterias << " materia(s) usan esta franja. Elimine esas materias primero." << endl; return;
    }
    cout << "Se eliminara: "; f->mostrar();
    if (!confirmar("Confirma")) return cancelar();
    franjas.eliminar(id);
    guardar(franjas, archivoFranjas);
    cout << "OK: franja eliminada." << endl;
}

void SistemaAsistencia::buscarFranja() {
    buscarEn(franjas, "Buscar (ID u hora, ej. H1 o 07:00): ", [](const FranjaHorario& f, const string& t) {
        return contieneTexto(f.getIdHorario(), t) || contieneTexto(minutosAHora(f.getHoraInicioMinutos()), t) ||
               contieneTexto(minutosAHora(f.getHoraFinMinutos()), t);
    });
}

void SistemaAsistencia::modificarFranja() {
    FranjaHorario* f = pedir(franjas, "ID de la franja a modificar: ", esIdValido, "ID invalido.", "ERROR: no existe esa franja.");
    if (f == nullptr) return;
    string id = f->getId();

    bool abierta = false;
    materias.paraCada([&](const Materia& m) {
        if (m.getIdHorarioAsociado() != id) return;
        const string c = m.getCedulaProfesor();
        if (tienePendienteHoy(c) && claseAbierta[c].idMateria == m.getIdMateria()) abierta = true;
    });
    if (abierta) {
        cout << "DENEGADO: hay una entrada sin salida en una materia de esta franja; registre primero la salida." << endl;
        return;
    }

    cout << "Actual: "; f->mostrar();
    cout << "Las franjas duran exactamente 2 horas y van entre " << minutosAHora(HORA_APERTURA)
         << " y " << minutosAHora(HORA_CIERRE) << ". El fin se calcula solo." << endl;
    int ini = 0;
    string motivo;
    while (true) {
        if (!leerHora("Nueva hora de inicio (HH:MM): ", ini)) return cancelar();
        if (!esFranjaValida(ini, ini + DURACION_FRANJA, motivo)) {
            cout << "  Inicio invalido: " << motivo << " (ENTER vacio = cancelar)" << endl; continue;
        }
        string choque, afectada;
        materias.paraCada([&](const Materia& m) {
            if (!choque.empty() || m.getIdHorarioAsociado() != id) return;
            string otra;
            if (hayConflictoHorario(m.getCedulaProfesor(), m.getIdMateria(), ini, ini + DURACION_FRANJA, otra)) {
                choque = otra;
                afectada = m.getIdMateria();
            }
        });
        if (choque.empty()) break;
        cout << "  Ese horario cruza " << afectada << " con " << choque
             << " (mismo profesor). Pruebe otra hora. (ENTER vacio = cancelar)" << endl;
    }
    f->setHoras(ini, ini + DURACION_FRANJA);
    guardar(franjas, archivoFranjas);
    cout << "OK: franja modificada: "; f->mostrar();
}

void SistemaAsistencia::agregarMateria() {
    if (franjas.getTamano() == 0)    { cout << "ERROR: primero debe existir al menos una franja." << endl; return; }
    if (profesores.getTamano() == 0) { cout << "ERROR: primero debe existir al menos un profesor." << endl; return; }

    cout << "(ENTER vacio = cancelar)" << endl;
    string id, nombre, idFr, ced;
    if (!leerCampo("ID de la materia (ej. M04): ", esIdValido, ERR_ID, id)) return cancelar();
    id = aMayusculas(id);
    if (materias.buscar(id) != nullptr) { cout << "ERROR: ya existe una materia con ese ID." << endl; return; }
    if (!leerCampo("Nombre de la materia: ", esTextoValido,
                   "Nombre invalido: 1 a 60 caracteres, sin '|'.", nombre)) return cancelar();

    cout << "Franjas disponibles:" << endl; franjas.imprimir();
    if (!leerCampo("ID de la franja: ", esIdValido, "ID invalido.", idFr)) return cancelar();
    idFr = aMayusculas(idFr);
    const FranjaHorario* nueva = franjas.buscar(idFr);
    if (nueva == nullptr) { cout << "ERROR: esa franja no existe." << endl; return; }

    cout << "Profesores disponibles:" << endl; profesores.imprimir();
    if (!leerCampo("Cedula del profesor: ", esCedulaValida, MSG_CEDULA_INVALIDA, ced)) return cancelar();
    if (profesores.buscar(ced) == nullptr) { cout << "ERROR: ese profesor no existe." << endl; return; }

    string choque;
    if (hayConflictoHorario(ced, "", nueva->getHoraInicioMinutos(), nueva->getHoraFinMinutos(), choque)) {
        cout << "ERROR: el profesor ya dicta " << choque << " en un horario que se cruza con esa franja." << endl; return;
    }

    materias.agregar(Materia(id, nombre, idFr, ced));
    guardar(materias, archivoMaterias);
    cout << "OK: materia agregada." << endl;
}

void SistemaAsistencia::eliminarMateria() {
    Materia* m = pedir(materias, "ID de la materia a eliminar: ", esIdValido, "ID invalido.", "ERROR: no existe esa materia.");
    if (m == nullptr) return;
    string id = m->getId(), ced = m->getCedulaProfesor();

    if (tienePendienteHoy(ced) && claseAbierta[ced].idMateria == id) {
        cout << "DENEGADO: hay una entrada sin salida en esta materia; registre primero la salida." << endl; return;
    }
    cout << "Se eliminara: "; m->mostrar();
    if (!confirmar("Confirma")) return cancelar();
    materias.eliminar(id);
    guardar(materias, archivoMaterias);
    cout << "OK: materia eliminada." << endl;
}

void SistemaAsistencia::buscarMateria() {
    buscarEn(materias, "Buscar (ID, nombre, franja o cedula del profesor): ", [](const Materia& m, const string& t) {
        return contieneTexto(m.getIdMateria(), t) || contieneTexto(m.getNombreMateria(), t) ||
               contieneTexto(m.getIdHorarioAsociado(), t) || contieneTexto(m.getCedulaProfesor(), t);
    });
}

void SistemaAsistencia::modificarMateria() {
    Materia* m = pedir(materias, "ID de la materia a modificar: ", esIdValido, "ID invalido.", "ERROR: no existe esa materia.");
    if (m == nullptr) return;
    string id = m->getId();

    const string cedActual = m->getCedulaProfesor();
    if (tienePendienteHoy(cedActual) && claseAbierta[cedActual].idMateria == id) {
        cout << "DENEGADO: hay una entrada sin salida en esta materia; registre primero la salida." << endl; return;
    }

    cout << "Actual: "; m->mostrar();
    cout << "(ENTER vacio = conservar el dato actual; el ID no se puede cambiar)" << endl;
    string nombre = m->getNombreMateria(), idFr = m->getIdHorarioAsociado(), ced = cedActual, tmp;

    leerCampoOpcional("Nuevo nombre: ", esTextoValido, "Nombre invalido: 1 a 60 caracteres, sin '|'.", nombre);
    if (g_eof) return cancelar();

    cout << "Franjas disponibles:" << endl; franjas.imprimir();
    if (leerCampoOpcional("Nueva franja (ID): ", esIdValido, "ID invalido.", tmp)) {
        tmp = aMayusculas(tmp);
        if (franjas.buscar(tmp) == nullptr) { cout << "ERROR: esa franja no existe. No se hizo ningun cambio." << endl; return; }
        idFr = tmp;
    }
    if (g_eof) return cancelar();

    cout << "Profesores disponibles:" << endl; profesores.imprimir();
    if (leerCampoOpcional("Nueva cedula del profesor: ", esCedulaValida, MSG_CEDULA_INVALIDA, tmp)) {
        if (profesores.buscar(tmp) == nullptr) { cout << "ERROR: ese profesor no existe. No se hizo ningun cambio." << endl; return; }
        ced = tmp;
    }
    if (g_eof) return cancelar();

    if (nombre == m->getNombreMateria() && idFr == m->getIdHorarioAsociado() && ced == cedActual) {
        cout << "Sin cambios." << endl; return;
    }
    const FranjaHorario* fr = franjas.buscar(idFr);
    string choque;
    if (hayConflictoHorario(ced, id, fr->getHoraInicioMinutos(), fr->getHoraFinMinutos(), choque)) {
        cout << "ERROR: el profesor ya dicta " << choque
             << " en un horario que se cruza con esa franja. No se hizo ningun cambio." << endl; return;
    }
    m->setNombreMateria(nombre);
    m->setIdHorarioAsociado(idFr);
    m->setCedulaProfesor(ced);
    guardar(materias, archivoMaterias);
    cout << "OK: materia modificada: "; m->mostrar();
}

void SistemaAsistencia::menuReportes() {
    while (!g_eof) {
        cout << "\n--- REPORTES ---" << endl;
        cout << "1. Registros de un profesor\n2. Registros de una fecha\n3. Horario de un profesor\n"
                "4. Horas dictadas por profesor\n5. Clases pendientes de salida (hoy)\n"
                "6. Resumen general\n7. Exportar registros a CSV (Excel)\n0. Volver" << endl;
        string t = leer("Opcion: ");
        if (g_eof) return;
        int op;
        if (!parsearEntero(t, op) || op > 7) { cout << "Opcion invalida." << endl; continue; }
        switch (op) {
            case 0: return;
            case 1: reporteRegistrosProfesor(); break;
            case 2: reporteRegistrosFecha();    break;
            case 3: reporteHorarioProfesor();   break;
            case 4: reporteHorasDictadas();     break;
            case 5: reportePendientes();        break;
            case 6: reporteResumen();           break;
            case 7: exportarCsv();              break;
        }
    }
}

void SistemaAsistencia::reporteRegistrosProfesor() {
    PersonaProfesor* p = pedir(profesores, "Cedula del profesor: ", esCedulaValida, MSG_CEDULA_INVALIDA, ERR_PROFESOR);
    if (p == nullptr) return;
    string ced = p->getCedula();
    listarRegistros(registros, "--- Registros de " + p->getNombre() + " " + p->getApellido() + " ---",
                    [&](const Registro& r) { return r.getCedula() == ced; });
}

void SistemaAsistencia::reporteRegistrosFecha() {
    string f = leer("Fecha AAAA-MM-DD (ENTER = hoy): ");
    if (g_eof) return;
    if (f.empty()) f = fechaActual();
    else if (!esFechaValida(f)) { cout << "Fecha invalida. Ejemplo: 2026-11-02" << endl; return; }
    listarRegistros(registros, "--- Registros del " + f + " ---", [&](const Registro& r) { return r.getFecha() == f; });
}

void SistemaAsistencia::reporteHorarioProfesor() {
    PersonaProfesor* p = pedir(profesores, "Cedula del profesor: ", esCedulaValida, MSG_CEDULA_INVALIDA, ERR_PROFESOR);
    if (p == nullptr) return;
    string ced = p->getCedula();

    struct Fila { int ini, fin; string idMateria, nombre, idFranja; };
    vector<Fila> filas;
    materias.paraCada([&](const Materia& m) {
        if (m.getCedulaProfesor() != ced) return;
        const FranjaHorario* f = franjas.buscar(m.getIdHorarioAsociado());
        if (f == nullptr) return;
        Fila x = { f->getHoraInicioMinutos(), f->getHoraFinMinutos(), m.getIdMateria(), m.getNombreMateria(), f->getIdHorario() };
        filas.push_back(x);
    });
    sort(filas.begin(), filas.end(), [](const Fila& a, const Fila& b) { return a.ini < b.ini; });

    cout << "--- Horario de " << p->getNombre() << " " << p->getApellido() << " ---" << endl;
    if (filas.empty()) { cout << "  (no tiene materias asignadas)" << endl; return; }
    for (size_t i = 0; i < filas.size(); i++)
        cout << "  " << minutosAHora(filas[i].ini) << " - " << minutosAHora(filas[i].fin) << " | "
             << filas[i].idMateria << " - " << filas[i].nombre << " (" << filas[i].idFranja << ")" << endl;
}

void SistemaAsistencia::reporteHorasDictadas() {
    map<string, int> abiertas, minutosProf, clasesProf, sinSalida;
    registros.paraCada([&](const Registro& r) {
        string clave = r.getCedula() + "#" + r.getIdMateria() + "#" + r.getFecha();
        if (r.getTipo() == 'E') { abiertas[clave] = r.getMinutos(); return; }
        auto it = abiertas.find(clave);
        if (it == abiertas.end()) return;
        int d = r.getMinutos() - it->second;
        if (d >= 0) { minutosProf[r.getCedula()] += d; clasesProf[r.getCedula()]++; }
        abiertas.erase(it);
    });
    for (auto it = abiertas.begin(); it != abiertas.end(); ++it)
        sinSalida[it->first.substr(0, it->first.find('#'))]++;

    cout << "--- Horas dictadas por profesor (entrada -> salida) ---" << endl;
    if (profesores.getTamano() == 0) { cout << "  (no hay profesores)" << endl; return; }
    profesores.paraCada([&](const PersonaProfesor& p) {
        const string c = p.getCedula();
        cout << "  " << c << " | " << p.getNombre() << " " << p.getApellido()
             << " | clases completas: " << clasesProf[c] << " | tiempo: " << duracion(minutosProf[c]);
        if (sinSalida[c] > 0) cout << " | entradas sin salida: " << sinSalida[c];
        cout << endl;
    });
}

void SistemaAsistencia::reportePendientes() {
    vector<string> ceds;
    for (auto it = claseAbierta.begin(); it != claseAbierta.end(); ++it) ceds.push_back(it->first);

    cout << "--- Clases con entrada y sin salida (hoy) ---" << endl;
    int n = 0;
    for (size_t i = 0; i < ceds.size(); i++) {
        if (!tienePendienteHoy(ceds[i])) continue;
        const AperturaClase& a = claseAbierta[ceds[i]];
        const PersonaProfesor* p = profesores.buscar(ceds[i]);
        const Materia* m = materias.buscar(a.idMateria);
        const FranjaHorario* f = (m != nullptr) ? franjas.buscar(m->getIdHorarioAsociado()) : nullptr;
        cout << "  " << (p != nullptr ? p->getNombre() + " " + p->getApellido() : ceds[i]) << " | Materia: " << a.idMateria;
        if (f != nullptr) cout << " | salida hasta las " << minutosAHora(f->getHoraFinMinutos() + TOLERANCIA_MIN);
        cout << endl;
        n++;
    }
    if (n == 0) cout << "  (ninguna)" << endl;
}

void SistemaAsistencia::reporteResumen() {
    int entradas = 0, salidas = 0;
    map<string, pair<int, int> > porMateria;
    registros.paraCada([&](const Registro& r) {
        if (r.getTipo() == 'E') { entradas++; porMateria[r.getIdMateria()].first++; }
        else                    { salidas++;  porMateria[r.getIdMateria()].second++; }
    });
    cout << "--- Resumen general ---" << endl;
    cout << "  Profesores: " << profesores.getTamano() << " | Materias: " << materias.getTamano()
         << " | Franjas: " << franjas.getTamano() << endl;
    cout << "  Registros: " << registros.getTamano() << " (entradas: " << entradas
         << ", salidas: " << salidas << ")" << endl;
    if (porMateria.empty()) return;
    cout << "  Por materia (entradas/salidas):" << endl;
    for (auto it = porMateria.begin(); it != porMateria.end(); ++it) {
        const Materia* m = materias.buscar(it->first);
        cout << "    " << it->first << (m != nullptr ? " - " + m->getNombreMateria() : string(" (eliminada)"))
             << ": " << it->second.first << "/" << it->second.second << endl;
    }
}

void SistemaAsistencia::exportarCsv() {
    const char* nombre = "registros.csv";
    ofstream out(nombre, ios::trunc);
    if (!out.is_open()) { cout << "ERROR: no se pudo crear " << nombre << "." << endl; return; }
    out << "\xEF\xBB\xBF" << "Fecha;Hora;Tipo;Cedula;Profesor;IdMateria;Materia\n";
    int n = 0;
    registros.paraCada([&](const Registro& r) {
        const PersonaProfesor* p = profesores.buscar(r.getCedula());
        const Materia* m = materias.buscar(r.getIdMateria());
        out << r.getFecha() << ";" << minutosAHora(r.getMinutos()) << ";"
            << (r.getTipo() == 'E' ? "ENTRADA" : "SALIDA") << ";"
            << "=\"" << r.getCedula() << "\";"
            << campoCsv(p != nullptr ? p->getNombre() + " " + p->getApellido() : string("(eliminado)")) << ";"
            << campoCsv(r.getIdMateria()) << ";"
            << campoCsv(m != nullptr ? m->getNombreMateria() : string("(eliminada)")) << "\n";
        n++;
    });
    out.flush();
    if (!out.good()) { cout << "ERROR: fallo al escribir " << nombre << "." << endl; return; }
    cout << "OK: " << n << " registro(s) exportados a " << nombre << "." << endl;
}
