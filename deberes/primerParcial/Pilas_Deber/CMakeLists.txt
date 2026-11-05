cmake_minimum_required(VERSION 3.20)
project(Proyecto_pilas)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto_pilas
        main.cpp
        Persona.h Persona.cpp
        Nodo.h Nodo.cpp
        Pila.h Pila.cpp
        Insertar.h Insertar.cpp
        Eliminar.h Eliminar.cpp
        Buscar.h Buscar.cpp
        Imprimir.h Imprimir.cpp
)
