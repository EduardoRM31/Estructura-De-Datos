#ifndef FRANJAHORARIO_H
#define FRANJAHORARIO_H

#include <string>

class FranjaHorario {
private:
    std::string idHorario;
    int horaInicioMinutos;
    int horaFinMinutos;
public:
    FranjaHorario(const std::string& id = "", int ini = 0, int fin = 0);

    std::string getIdHorario() const;
    int getHoraInicioMinutos() const;
    int getHoraFinMinutos() const;

    std::string getId() const;
    void mostrar() const;

    void setHoras(int ini, int fin);

    std::string serializar() const;
    static bool deserializar(const std::string& linea, FranjaHorario& f);
};

#endif
