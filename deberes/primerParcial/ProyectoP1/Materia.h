#ifndef MATERIA_H
#define MATERIA_H

#include <string>

class Materia {
private:
    std::string idMateria;
    std::string nombreMateria;
    std::string idHorarioAsociado;
    std::string cedulaProfesor;
public:
    Materia(const std::string& id = "", const std::string& nombre = "",
            const std::string& idHorario = "", const std::string& cedProf = "");

    std::string getIdMateria() const;
    std::string getNombreMateria() const;
    std::string getIdHorarioAsociado() const;
    std::string getCedulaProfesor() const;

    std::string getId() const;
    void mostrar() const;

    void setNombreMateria(const std::string& n);
    void setIdHorarioAsociado(const std::string& id);
    void setCedulaProfesor(const std::string& ced);

    std::string serializar() const;
    static bool deserializar(const std::string& linea, Materia& m);
};

#endif
