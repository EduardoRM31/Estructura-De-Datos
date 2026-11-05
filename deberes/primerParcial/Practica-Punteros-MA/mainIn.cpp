
#include <iostream>
using namespace std;
 
// Invierte el arreglo usando dos punteros (sin usar [])
void invertir(int *arreglo, int n){
    int *inicio = arreglo;
    int *fin = arreglo + n - 1;
 
    while(inicio < fin){
        int aux = *inicio;
        *inicio = *fin;
        *fin = aux;
 
        inicio++;
        fin--;
    }
}
 
// Imprime el arreglo con punteros
void imprimir(int *arreglo, int n){
    for(int i = 0; i < n; i++){
        cout << *(arreglo + i) << " ";
    }
    cout << endl;
}
 
int main(){
    int n;
    cout << "Cuantos elementos desea? ";
    cin >> n;
 
    if(n <= 0){
        cout << "El tamano debe ser mayor que 0." << endl;
        return 1;
    }
 
    int *arreglo = new int[n];
 
    for(int i = 0; i < n; i++){
        cout << "Elemento " << i + 1 << ": ";
        cin >> *(arreglo + i);
    }
 
    cout << "Original: ";
    imprimir(arreglo, n);
 
    invertir(arreglo, n);
 
    cout << "Invertido: ";
    imprimir(arreglo, n);
 
    delete[] arreglo;
    arreglo = nullptr;
 
    return 0;
}
 
#include <iostream>
using namespace std;
 
// Invierte el arreglo usando dos punteros (sin usar [])
void invertir(int *arreglo, int n){
    int *inicio = arreglo;
    int *fin = arreglo + n - 1;
 
    while(inicio < fin){
        int aux = *inicio;
        *inicio = *fin;
        *fin = aux;
 
        inicio++;
        fin--;
    }
}
 
// Imprime el arreglo con punteros
void imprimir(int *arreglo, int n){
    for(int i = 0; i < n; i++){
        cout << *(arreglo + i) << " ";
    }
    cout << endl;
}
 
int main(){
    int n;
    cout << "Cuantos elementos desea? ";
    cin >> n;
 
    if(n <= 0){
        cout << "El tamano debe ser mayor que 0." << endl;
        return 1;
    }
 
    int *arreglo = new int[n];
 
    for(int i = 0; i < n; i++){
        cout << "Elemento " << i + 1 << ": ";
        cin >> *(arreglo + i);
    }
 
    cout << "Original: ";
    imprimir(arreglo, n);
 
    invertir(arreglo, n);
 
    cout << "Invertido: ";
    imprimir(arreglo, n);
 
    delete[] arreglo;
    arreglo = nullptr;
 
    return 0;
}
 