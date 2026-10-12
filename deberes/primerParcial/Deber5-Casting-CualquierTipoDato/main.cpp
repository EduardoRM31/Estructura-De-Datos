#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    char dato[50];

    printf("Ingresa un dato: ");
    scanf("%49s", dato);   

    if (strlen(dato) == 1 && !isdigit(dato[0])) {
        char c = dato[0];
        printf("Es un CARACTER: %c\n", c);
        printf("Casting a int   : %d\n", (int)c);    
        printf("Casting a float : %f\n", (float)c);
    }

    else if (strchr(dato, '.') != NULL) {
        float f = atof(dato);
        printf("Es un DECIMAL: %f\n", f);
        printf("Casting a int    : %d\n", (int)f);   
        printf("Casting a double : %f\n", (double)f);
    }

    else if (isdigit(dato[0]) || (dato[0] == '-' && isdigit(dato[1]))) {
        int n = atoi(dato);
        printf("Es un ENTERO: %d\n", n);
        printf("Casting a float  : %f\n", (float)n);
        printf("Casting a double : %f\n", (double)n);
        if (n >= 32 && n <= 126)
            printf("Casting a char   : %c\n", (char)n);
        else
            printf("Casting a char   : (no se puede mostrar)\n");
    }

    else {
        printf("Es una CADENA de texto: %s\n", dato);
        printf("No se puede hacer casting a numero.\n");
    }

    return 0;
}