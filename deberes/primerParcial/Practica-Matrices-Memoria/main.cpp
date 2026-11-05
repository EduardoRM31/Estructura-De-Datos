#include <iostream>
#include <stdlib.h>

using namespace std;

void encerar(int **); //Inicializar para que no de basura
void ingresar(int **, const char*);
void multiplicar(int **, int **, int **);
void imprimir(int **, const char*);
int **segmentarMatriz();
void liberar(int **);

void encerar(int ** matriz){
    for(int fila=0; fila<3; fila++){
        for(int col=0;col<3;col++){
            //matriz[fila][col]=0;
            *(*(matriz+fila)+col)=0;
        }
    }
}

int **segmentarMatriz(){
    int **matriz=static_cast<int**>(std::malloc(3*sizeof(int*)));
    if(matriz==nullptr){
        return nullptr;
    }

    for(int fila=0; fila<3;fila++){
        *(matriz+fila) = static_cast<int*>(std::malloc(3*sizeof(int*)));
        if(*(matriz+fila)==nullptr){
            while(fila>0){
                --fila;
                std::free(*(matriz+fila));
            }
            std::free(matriz);
            return nullptr;
        }
    }
    return nullptr;
}