//Invierte un arreglo usando dos punteros, uno al inicio y otro al final, 
//que se van acercando e intercambian valores.

#include <iostream>
using namespace std;
 
int main(){
    int arreglo[5] = {1, 2, 3, 4, 5};
 
    int *inicio = arreglo;       // apunta al primer elemento
    int *fin = arreglo + 4;      // apunta al ultimo elemento
 
    cout << "Original: ";
    for(int i = 0; i < 5; i++){
        cout << *(arreglo + i) << " ";
    }
    cout << endl;
 
    while(inicio < fin){
        int aux = *inicio;       // guardo el valor de inicio
        *inicio = *fin;          // inicio recibe el valor de fin
        *fin = aux;              // fin recibe el valor guardado
 
        inicio++;                // inicio avanza a la derecha
        fin--;                   // fin retrocede a la izquierda
    }
 
    cout << "Invertido: ";
    for(int i = 0; i < 5; i++){
        cout << *(arreglo + i) << " ";
    }
    cout << endl;
 
    return 0;
}
 