#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype> 
using namespace std;

class Persona{
    private:
    string cedula;
    string nombre;
    string apellido;
    int id;

    public:
    Persona() { id = 0; }
    Persona(string cedula, string nombre, string apellido){
        this->cedula = cedula;
        this->nombre = nombre;
        this->apellido = apellido;
        id = 0;
    }

    static void validarCedula(const string& c){
        if(c.size() != 10){
            throw invalid_argument("La cedula debe tener exactamente 10 digitos.");
        }
        for(size_t i = 0; i < c.size(); i++){
            if(!isdigit((unsigned char)c[i])){
                throw invalid_argument("La cedula solo debe contener numeros.");
            }
        }
        int provincia = stoi(c.substr(0, 2));
        if(!((provincia >= 1 && provincia <= 24) || provincia == 30)){
            throw invalid_argument("Los dos primeros digitos deben estar entre 01 y 24, o ser 30.");
        }
    }

    static void validarTexto(const string& t, const string& campo){
        if(t.empty()){
            throw invalid_argument(campo + " no puede estar vacio.");
        }
        if(t.size() > 40){
            throw invalid_argument(campo + " es demasiado largo (maximo 40 caracteres).");
        }
        for(size_t i = 0; i < t.size(); i++){

            unsigned char ch = (unsigned char)t[i];

            if(!(isalpha(ch) || ch == ' ' || ch >= 128)){
                throw invalid_argument(campo + " solo debe contener letras.");
            }
        }
    }


    string getCedula(){
        return cedula; }
    string getNombre(){
        return nombre; }
    string getApellido(){
        return apellido; }
    int getId() const {
        return id; }

    void setCedula(string cedula){
        validarCedula(cedula);
        this->cedula = cedula;
    }
    void setNombre(string nombre){
        validarTexto(nombre, "El nombre");
        this->nombre = nombre;
    }
    void setApellido(string apellido){
        validarTexto(apellido, "El apellido");
        this->apellido = apellido;
    }
    void setId(int id){
        this->id = id;
    }

    bool operator==(const Persona& otra) const {
        return cedula == otra.cedula;
    }

    friend ostream& operator<<(ostream& salida, const Persona& p){
        salida << "ID " << p.id << " - " << p.cedula << " - " << p.nombre << " " << p.apellido;
        return salida;
    }
};


#endif