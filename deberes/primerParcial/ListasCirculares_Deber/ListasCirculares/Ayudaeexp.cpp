#include <iostream>
#include <string>
using namespace std;

class Persona {
public:
    string ced, nom, ap;
    Persona(string c, string n, string a) : ced(c), nom(n), ap(a) {}
};

class Nodo {
public:
    Persona p;
    Nodo* sig;
    Nodo* ant;
    Nodo(Persona persona) : p(persona), sig(nullptr), ant(nullptr) {}

    static void insertar(Nodo*& cab, string c, string n, string a) {
        Nodo* nuevo = new Nodo(Persona(c, n, a));
        if (!cab) {
            cab = nuevo;
            cab->sig = cab;
            cab->ant = cab;
            return;
        }
        Nodo* ult = cab->ant;
        ult->sig = nuevo;
        nuevo->ant = ult;
        nuevo->sig = cab;
        cab->ant = nuevo;
    }

    static void buscar(Nodo* cab, string ced) {
        if (!cab) return;
        Nodo* act = cab;
        do {
            if (act->p.ced == ced) {
                cout << "Encontrado: " << act->p.nom << endl;
                return;
            }
            act = act->sig;
        } while (act != cab);
    }

    static void imprimir(Nodo* cab) {
        if (!cab) return;
        Nodo* act = cab;
        do {
            cout << act->p.nom << " -> ";
            act = act->sig;
        } while (act != cab);
        cout << "(fin)\n";
    }

    static void eliminar(Nodo*& cab, string ced) {
        if (!cab) return;
        Nodo* act = cab;
        bool enc = false;
        do {
            if (act->p.ced == ced) {
                enc = true;
                break;
            }
            act = act->sig;
        } while (act != cab);

        if (!enc) return;

        if (act->sig == cab && act->ant == cab) {
            delete act;
            cab = nullptr;
            return;
        }

        act->ant->sig = act->sig;
        act->sig->ant = act->ant;

        if (act == cab) {
            cab = act->sig;
        }
        delete act;
    }
};

int main() {
    Nodo* cab = nullptr;
    Nodo::insertar(cab, "1", "Ana", "P");
    Nodo::insertar(cab, "2", "Luis", "G");
    Nodo::insertar(cab, "3", "Carlos", "R");
    
    Nodo::imprimir(cab);
    Nodo::buscar(cab, "2");
    Nodo::eliminar(cab, "1");
    Nodo::imprimir(cab);

    return 0;
}