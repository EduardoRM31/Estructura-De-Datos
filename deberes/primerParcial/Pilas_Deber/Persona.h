#pragma once
#include <string>

class Persona {
private:
    std::string nombre;
    std::string cedula;
    std::string apellido;

public:
    Persona();
    Persona(const std::string& nombre, const std::string& cedula, const std::string& apellido);

    std::string getNombre() const;
    std::string getApellido() const;
    std::string getCedula() const;

    void setNombre(const std::string& newNombre);
    void setApellido(const std::string& newApellido);
    void setCedula(const std::string& newCedula);

    void mostrar() const;

    // Método estático para validar cédula ecuatoriana
    static bool esCedulaValidaEcuador(const std::string& cedula);
};
