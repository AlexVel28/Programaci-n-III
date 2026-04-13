#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* sig;
};

void push(Nodo*& pila, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->sig = pila;
    pila = nuevo;
}

void pop(Nodo*& pila) {
    if (pila == NULL) {
        cout << "Pila vacia\n";
        return;
    }
    Nodo* aux = pila;
    pila = pila->sig;
    delete aux;11
}

void mostrarPila(Nodo* pila) {
    if (pila == NULL) {
        cout << "Pila vacia\n";
        return;
    }
    while (pila != NULL) {
        cout << pila->dato << " -> ";
        pila = pila->sig;
    }
    cout << "NULL\n";
}

void enqueue(Nodo*& frente, Nodo*& fin, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->sig = NULL;

    if (frente == NULL) frente = nuevo;
    else fin->sig = nuevo;

    fin = nuevo;
}

void dequeue(Nodo*& frente, Nodo*& fin) {
    if (frente == NULL) {
        cout << "Cola vacia\n";
        return;
    }
    Nodo* aux = frente;
    frente = frente->sig;
    if (frente == NULL) fin = NULL;
    delete aux;
}

void mostrarCola(Nodo* frente) {
    if (frente == NULL) {
        cout << "Cola vacia\n";
        return;
    }
    while (frente != NULL) {
        cout << frente->dato << " -> ";
        frente = frente->sig;
    }
    cout << "NULL\n";
}

void insertarLista(Nodo*& lista, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->sig = lista;
    lista = nuevo;
}

void ordenarLista(Nodo* lista) {
    if (lista == NULL) return;

    Nodo* i;
    Nodo* j;
    int temp;

    for (i = lista; i != NULL; i = i->sig) {
        for (j = i->sig; j != NULL; j = j->sig) {
            if (i->dato > j->dato) {
                temp = i->dato;
                i->dato = j->dato;
                j->dato = temp;
            }
        }
    }
}

void mostrarLista(Nodo* lista) {
    if (lista == NULL) {
        cout << "Lista vacia\n";
        return;
    }
    while (lista != NULL) {
        cout << lista->dato << " -> ";
        lista = lista->sig;
    }
    cout << "NULL\n";
}

// ===== LIBERAR MEMORIA =====
void liberar(Nodo*& lista) {
    while (lista != NULL) {
        Nodo* aux = lista;
        lista = lista->sig;
        delete aux;
    }
}

int main() {
    Nodo* pila = NULL;
    Nodo* frente = NULL;
    Nodo* fin = NULL;
    Nodo* lista = NULL;

    int opcion, num;
    int contPares = 0, contImpares = 0;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Ingresar numero\n";
        cout << "2. Mostrar pila (impares)\n";
        cout << "3. Mostrar cola (pares)\n";
        cout << "4. Mostrar lista (negativos)\n";
        cout << "5. Eliminar de pila\n";
        cout << "6. Eliminar de cola\n";
        cout << "7. Mostrar estadisticas\n";
        cout << "8. Ordenar lista de negativos\n";
        cout << "9. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingrese numero (-1 para salir): ";
            cin >> num;

            if (num == -1) break;

            if (num < 0) {
                insertarLista(lista, num);
            } else if (num % 2 == 0) {
                enqueue(frente, fin, num);
                contPares++;
            } else {
                push(pila, num);
                contImpares++;
            }
            break;

        case 2:
            mostrarPila(pila);
            break;

        case 3:
            mostrarCola(frente);
            break;

        case 4:
            mostrarLista(lista);
            break;

        case 5:
            pop(pila);
            break;

        case 6:
            dequeue(frente, fin);
            break;

        case 7:
            cout << "Cantidad de pares: " << contPares << endl;
            cout << "Cantidad de impares: " << contImpares << endl;
            break;

        case 8:
            ordenarLista(lista);
            cout << "Lista ordenada.\n";
            break;

        case 9:
            cout << "Liberando memoria...\n";
            liberar(pila);
            liberar(frente);
            liberar(lista);
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 9);

    return 0;
}