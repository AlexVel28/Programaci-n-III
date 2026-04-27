#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// --- ESTRUCTURAS DE DATOS (NODOS) ---

struct NodoSimple {
    int dato;
    NodoSimple* siguiente;
};

struct NodoDoble {
    int dato;
    string estructura;
    int orden;
    NodoDoble* siguiente;
    NodoDoble* anterior;
};

struct NodoArbol {
    int dato;
    NodoArbol *izq, *der;
};

// --- VARIABLES GLOBALES Y ESTADÍSTICAS ---
NodoSimple* pila = nullptr;
NodoSimple* colaFrente = nullptr;
NodoSimple* colaFinal = nullptr;
NodoSimple* listaNegativos = nullptr;
NodoDoble* historialInicio = nullptr;
NodoDoble* historialFin = nullptr;
NodoArbol* raizBST = nullptr;

int cantParesPos = 0, cantImparesPos = 0, cantNegativos = 0, cantCeros = 0;
int totalValidos = 0, ordenGlobal = 1;
int maxValor = -2147483648, minValor = 2147483647;

// --- FUNCIONES DE MEMORIA ---

void pushPila(int n) {
    NodoSimple* nuevo = new NodoSimple{n, pila};
    pila = nuevo;
}

void enqueue(int n) {
    NodoSimple* nuevo = new NodoSimple{n, nullptr};
    if (!colaFrente) colaFrente = nuevo;
    else colaFinal->siguiente = nuevo;
    colaFinal = nuevo;
}

void insertarListaSimple(NodoSimple*& lista, int n) {
    NodoSimple* nuevo = new NodoSimple{n, lista};
    lista = nuevo;
}

void insertarHistorial(int n, string est) {
    NodoDoble* nuevo = new NodoDoble{n, est, ordenGlobal++, nullptr, historialFin};
    if (!historialInicio) historialInicio = nuevo;
    else historialFin->siguiente = nuevo;
    historialFin = nuevo;
}

NodoArbol* insertarBST(NodoArbol* nodo, int n) {
    if (!nodo) return new NodoArbol{n, nullptr, nullptr};
    if (n < nodo->dato) nodo->izq = insertarBST(nodo->izq, n);
    else if (n > nodo->dato) nodo->der = insertarBST(nodo->der, n);
    return nodo;
}

// --- LOGICA DE NEGATIVOS (REGLA 4) ---

void procesarNegativos() {
    if (!listaNegativos) { cout << "Lista vacia.\n"; return; }

    cout << "Lista original: ";
    NodoSimple* temp = listaNegativos;
    while(temp) { cout << temp->dato << " "; temp = temp->siguiente; }

    int eliminados = 0;
    NodoSimple** curr = &listaNegativos;
    while (*curr) {
        if (abs((*curr)->dato) < 10) {
            NodoSimple* borrar = *curr;
            *curr = (*curr)->siguiente;
            delete borrar;
            eliminados++;
        } else {
            curr = &((*curr)->siguiente);
        }
    }
    cout << "\nNodos eliminados: " << eliminados << "\nLista resultante: ";
    temp = listaNegativos;
    while(temp) { cout << temp->dato << " "; temp = temp->siguiente; }
    cout << endl;
}

// --- REORGANIZACIÓN (REGLA 6) ---

void reorganizar() {
    NodoSimple *auxPila = nullptr, *auxCola = nullptr;
    // Vaciar Pila
    while(pila) {
        NodoSimple* t = pila;
        insertarListaSimple(auxPila, t->dato);
        pila = pila->siguiente;
        delete t;
    }
    // Vaciar Cola
    while(colaFrente) {
        NodoSimple* t = colaFrente;
        insertarListaSimple(auxCola, t->dato);
        colaFrente = colaFrente->siguiente;
        delete t;
    }
    // Reconstruir BST (simplificado: insertar desde listas aux)
    auto insAux = [](NodoSimple* l) {
        while(l) { raizBST = insertarBST(raizBST, l->dato); l = l->siguiente; }
    };
    insAux(auxPila); insAux(auxCola);
    cout << "Estructuras reorganizadas y BST reconstruido.\n";
}

// --- RECORRIDOS BST ---
void inOrden(NodoArbol* r) { if(r){ inOrden(r->izq); cout<<r->dato<<" "; inOrden(r->der); } }
void preOrden(NodoArbol* r) { if(r){ cout<<r->dato<<" "; preOrden(r->izq); preOrden(r->der); } }
void postOrden(NodoArbol* r) { if(r){ postOrden(r->izq); postOrden(r->der); cout<<r->dato<<" "; } }

// --- MENÚ Y MAIN ---

int main() {
    int opcion, n, cantidad;
    do {
        cout << "\n--- MENU SISTEMA ---\n1. Ingresar N numeros\n2. Mostrar Pila\n3. Mostrar Cola\n4. Lista Negativos\n5. Historial\n6. Construir BST\n7. Eliminar Negativos (<10)\n9. Estadisticas\n10. Reorganizar\n11. Salir\nOpcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Cantidad: "; cin >> cantidad;
                if(cantidad <= 0) break;
                for(int i=0; i<cantidad; i++){
                    cout << "Numero: "; cin >> n;
                    if (n > 0) {
                        if (n % 2 == 0) { enqueue(n); insertarHistorial(n, "COLA"); cantParesPos++; }
                        else { pushPila(n); insertarHistorial(n, "PILA"); cantImparesPos++; }
                        totalValidos++;
                    } else if (n < 0) {
                        insertarListaSimple(listaNegativos, n);
                        insertarHistorial(n, "LISTA SIMPLE");
                        cantNegativos++; totalValidos++;
                    } else cantCeros++;

                    if (n != 0) {
                        if (n > maxValor) maxValor = n;
                        if (n < minValor) minValor = n;
                    }
                }
                break;
            case 5:
                { NodoDoble* t = historialInicio;
                  while(t){ cout << t->orden << ". " << t->dato << " (" << t->estructura << ")\n"; t = t->siguiente; }
                } break;
            case 6:
                // Construir BST desde datos positivos validos en historial
                { NodoDoble* t = historialInicio;
                  while(t){ if(t->dato > 0) raizBST = insertarBST(raizBST, t->dato); t = t->siguiente; }
                  cout << "InOrden: "; inOrden(raizBST); cout << "\nPreOrden: "; preOrden(raizBST); cout << "\nPostOrden: "; postOrden(raizBST); cout << endl;
                } break;
            case 7: procesarNegativos(); break;
            case 9:
                cout << "Pares+: " << cantParesPos << "\nImpares+: " << cantImparesPos << "\nNegativos: " << cantNegativos;
                cout << "\nCeros: " << cantCeros << "\nTotal validos: " << totalValidos;
                cout << "\nMax: " << maxValor << "\nMin: " << minValor << endl;
                break;
            case 10: reorganizar(); break;
        }
    } while (opcion != 11);

    return 0;
}