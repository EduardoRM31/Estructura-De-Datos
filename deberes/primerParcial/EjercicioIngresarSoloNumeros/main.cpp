#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int ingresar();
int ingresar(){
        int i = 0;
        char c;
        char datos[10];

        printf("%s", "Ingrese un numero: ");

        while((c = getch()) != 13){
            if(c >= '0' && c <= '9'){
                printf("%c", c);
                c = datos[i++];
            }
        }

        datos[i] = '\0';
        return atoi(datos);
}

int main(){

    int numero;
    numero = ingresar();
    printf("\nEl numero ingresado es: %d", numero);
    return 0;
}

/*debugger instalar para que se ejecute paso a paso
para la siguiente clase*/