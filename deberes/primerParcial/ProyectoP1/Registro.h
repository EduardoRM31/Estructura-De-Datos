#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

class Registro {
private:
    std::string cedula;
    std::string idMateria;
    char tipo;
    int minutos;
    std::string fecha;
public:
    Registro(const std::string& c = "", const std::string& m = "", char t = 'E',
             int min = 0, const std::string& f = "");

    std::string getCedula() const;
    std::string getIdMateria() const;
    char getTipo() const;
    std::string getFecha() const;
    int getMinutos() const;

    std::string getId() const;
    void mostrar() const;

    std::string serializar() const;
    static bool deserializar(const std::string& linea, Registro& r);
};

#endif
