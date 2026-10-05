#include "Estudiante.h"
#include <iostream>

Estudiante::Estudiante(){
    id = "";
    nombre = "";
    apellido = "";
}

Estudiante::Estudiante(std::string id, std::string nombre, std::string apellido) {
    this->id = id;
    this->nombre = nombre;
    this->apellido = apellido;
}

std::string Estudiante::getId() const { return id; }
std::string Estudiante::getNombre() const { return nombre; }
std::string Estudiante::getApellido() const { return apellido; }

void Estudiante::setId(std::string id) { 
    this->id = id; 
}
void Estudiante::setNombre(std::string nombre) {
    this->nombre = nombre; 
}
void Estudiante::setApellido(std::string apellido) {
    this->apellido = apellido; 
}

void Estudiante::mostrar() const {
    std::cout<<"ID: " << id <<std::endl;
    std::cout<<"Nombre: " << nombre << " " << apellido << std::endl;
}