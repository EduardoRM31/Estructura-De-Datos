#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>
using namespace std;

class Persona{
    private:
    string cedula;
    string nombre;
    string apellido;

    public:
    Persona() { }
    Persona(string cedula, string nombre, string apellido){
        this->cedula = cedula;
        this->nombre = nombre;
        this->apellido = apellido;
    }

    string getCedula(){ 
        return cedula;
    }

    string getNombre(){
        return nombre;
    }

    string getApellido(){
        return apellido;
    }

    void setCedula(string cedula){
        this->cedula = cedula;
    }

    void setNombre(string nombre){
        this->nombre = nombre;
    }

    void setApellido(string apellido){
        this->apellido = apellido;
    }

    bool operator==(const Persona& otra) const {
        return cedula == otra.cedula;
    }

    friend ostream& operator<<(ostream& salida, const Persona& p){
        salida << p.cedula << " - " << p.nombre << " " << p.apellido;
        return salida;
    }
};

#endif