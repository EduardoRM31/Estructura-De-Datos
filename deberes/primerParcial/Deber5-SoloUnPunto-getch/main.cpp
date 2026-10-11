#include <stdio.h>
#include <conio.h>

#define MAX 20

int main(){
    int c;
    char numero[MAX];
    int len = 0;
    int tienePunto = 0;

    numero[0] = '\0';

    while(1){
        c = getch();

        if(c == 0 || c == 224){
            getch();
            break;
        }

        if (c == '\r' || c == '\n') {
            if (len == 0) {
                continue;
            }
            if (numero[len - 1] == '.') {
                printf("\n  [Error] Numero incompleto (termina en punto).\n");
                printf("Ingrese un numero: %s", numero);
                continue;
            }
            break;
        }

        if(c == '\b'){
            if(len > 0){
                len--;
                if(numero[len] == '.'){
                    tienePunto = 0;
                }
                numero[len] = '\0';
                printf("\b \b");
            }
            continue;
        }

       if(c >= '0' && c <= '9'){
            if(len < MAX - 1){
                numero[len] = (char)c;
                len++;
                numero[len] = '\0';
                putchar(c);
            }
            continue;
       }

       if(c == '.'){
            if(len > 0 && tienePunto == 0){
                if(len < MAX - 1){
                    numero[len] = '.';
                    len++;
                    numero[len] = '\0';
                    tienePunto = 1;
                    putchar('.');
                }
            }
            continue;
       }

        printf("\nUsted ingreso: %s\n", numero);
    }

    return 0;
}