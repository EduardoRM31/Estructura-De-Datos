#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona {
protected:
    std::string cedula;
    std::string nombre;
    std::string apellido;
public:
    Persona(const std::string& c = "", const std::string& n = "", const std::string& a = "");
    virtual ~Persona() = 0;
    virtual void mostrarDatos() const = 0;

    std::string getCedula() const;
    std::string getNombre() const;
    std::string getApellido() const;
};

#endif
