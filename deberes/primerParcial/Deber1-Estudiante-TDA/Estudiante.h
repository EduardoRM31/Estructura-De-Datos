#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

class Estudiante {
    private:
        std::string id;
        std::string nombre;
        std::string apellido;

    public:
        Estudiante();
        Estudiante(std::string id, std::string nombre, std::string apellido);

        std::string getId() const;
        std::string getNombre() const;
        std::string getApellido() const;

        void setId(std::string id);
        void setNombre(std::string nombre);
        void setApellido(std::string apellido);

        void mostrar() const;
};

#endif

