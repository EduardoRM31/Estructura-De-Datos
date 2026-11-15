//Deber validar expresion matematica

#include <iostream>
using namespace std;

struct NodoChar {
    char dato;
    NodoChar* sig;
};

struct NodoPar {
    NodoPar* sig;
};

bool esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Lee la expresión carácter por carácter en memoria dinámica sin usar []
NodoChar* leerExpresionDinamica() {
    NodoChar* cabeza = nullptr;
    NodoChar* cola = nullptr;

    char c;
    while (cin.get(c) && c != '\n') {
        NodoChar* nuevo = new NodoChar;
        nuevo->dato = c;
        nuevo->sig = nullptr;

        if (cabeza == nullptr) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            cola->sig = nuevo;
            cola = nuevo;
        }
    }
    return cabeza;
}

// Libera toda la lista de caracteres
void liberarListaChar(NodoChar* p) {
    while (p != nullptr) {
        NodoChar* temp = p;
        p = p->sig;
        delete temp;
    }
}

// Libera cualquier paréntesis que haya quedado en la pila
void liberarPilaPar(NodoPar* tope) {
    while (tope != nullptr) {
        NodoPar* temp = tope;
        tope = tope->sig;
        delete temp;
    }
}

bool esValida(NodoChar* inicio) {
    NodoPar* tope = nullptr; // Pila dinámica de '('

    // true = toca número o '('
    // false = ya hubo número o ')', toca operador o ')'
    bool esperaValor = true;
    bool huboAlgo = false;

    NodoChar* p = inicio;

    while (p != nullptr) {
        char actual = p->dato;

        if (actual == ' ') {
            p = p->sig;
            continue;
        }

        huboAlgo = true;

        // 1. Número (puede tener varios dígitos seguidos)
        if (actual >= '0' && actual <= '9') {
            if (!esperaValor) {
                // Ej: "(2+3)2" -> falta '*'
                liberarPilaPar(tope);
                return false;
            }
            while (p != nullptr && p->dato >= '0' && p->dato <= '9') {
                p = p->sig;
            }
            esperaValor = false;
            continue;
        }

        // 2. Abre paréntesis '('
        if (actual == '(') {
            if (!esperaValor) {
                // Ej: "(2+3)(2)" o "2(3)" -> falta '*'
                liberarPilaPar(tope);
                return false;
            }
            NodoPar* nuevoPar = new NodoPar;
            nuevoPar->sig = tope;
            tope = nuevoPar;

            esperaValor = true;
            p = p->sig;
            continue;
        }

        // 3. Cierra paréntesis ')'
        if (actual == ')') {
            if (esperaValor || tope == nullptr) {
                // Ej: "()", "(2+)" o ")" sin '('
                liberarPilaPar(tope);
                return false;
            }
            NodoPar* temp = tope;
            tope = tope->sig;
            delete temp;

            esperaValor = false;
            p = p->sig;
            continue;
        }

        // 4. Operador (+, -, *, /)
        if (esOperador(actual)) {
            if (esperaValor) {
                // Ej: "+2", "(*3)", "2+*3"
                liberarPilaPar(tope);
                return false;
            }
            esperaValor = true;
            p = p->sig;
            continue;
        }

        // Cualquier otro símbolo no es válido
        liberarPilaPar(tope);
        return false;
    }

    bool sinParentesisAbiertos = (tope == nullptr);
    liberarPilaPar(tope);

    // No puede estar vacía, ni quedar esperando valor (ej. "2+"), ni tener '(' sin cerrar
    return huboAlgo && (!esperaValor) && sinParentesisAbiertos;
}

int main() {
    cout << "Escribe una expresion: ";
    NodoChar* expr = leerExpresionDinamica();

    if (esValida(expr)) {
        cout << "CORRECTA\n";
    } else {
        cout << "INCORRECTA\n";
    }

    liberarListaChar(expr);
    return 0;
}