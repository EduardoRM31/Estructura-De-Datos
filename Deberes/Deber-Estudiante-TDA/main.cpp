#include "Estudiante.h"

int main() {
    Estudiante e1;
    e1.setId("L000456628");
    e1.setNombre("Eduardo");
    e1.setApellido("Romero");
    e1.mostrar();

    Estudiante e2("L000252866", "Martina", "Unda");
    e2.mostrar();

    return 0;
}