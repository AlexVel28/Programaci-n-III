#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

Nodo* cima = nullptr;

void push(int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = cima;
    cima = nuevo;
    cout << "Elemento insertado correctamente.\n";
}

void pop() {
    if (cima == nullptr) {
        cout << "Error: la pila está vacía.\n";
        return;
    }
    Nodo* temp = cima;
    cout << "Elemento eliminado: " << temp->dato << endl;
    cima = cima->siguiente;
    delete temp;
}

void peek() {
    if (cima == nullptr) {
        cout << "La pila está vacía.\n";
        return;
    }
    cout << "Elemento en el tope: " << cima->dato << endl;
}

void mostrar() {
    if (cima == nullptr) {
        cout << "La pila está vacía.\n";
        return;
    }
    Nodo* actual = cima;
    cout << "Elementos de la pila:\n";
    while (actual != nullptr) {
        cout << actual->dato << endl;
        actual = actual->siguiente;
    }
}

int contarElementos() {
    int contador = 0;
    Nodo* actual = cima;
    while (actual != nullptr) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

void buscarElemento(int valor) {
    if (cima == nullptr) {
        cout << "La pila está vacía.\n";
        return;
    }
    Nodo* actual = cima;
    int posicion = 0;
    bool encontrado = false;

    while (actual != nullptr) {
        if (actual->dato == valor) {
            cout << "Elemento encontrado en posición: " << posicion << endl;
            encontrado = true;
            break;
        }
        actual = actual->siguiente;
        posicion++;
    }

    if (!encontrado) {
        cout << "Elemento no encontrado.\n";
    }
}

void vaciarPila() {
    while (cima != nullptr) {
        pop();
    }
    cout << "Pila vaciada completamente.\n";
}

void menu() {
    int opcion, valor;

    do {
        cout << "ALEX FERNANDO VELASQUEZ PORTILLO";
        cout << "\n===== MENU PILA =====\n";
        cout << "1. Insertar elemento (push)\n";
        cout << "2. Eliminar elemento del tope (pop)\n";
        cout << "3. Mostrar el tope (peek)\n";
        cout << "4. Mostrar toda la pila\n";
        cout << "5. Contar elementos\n";
        cout << "6. Buscar elemento\n";
        cout << "7. Vaciar pila\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese valor: ";
                cin >> valor;
                push(valor);
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                mostrar();
                break;
            case 5:
                cout << "Cantidad de elementos: " << contarElementos() << endl;
                break;
            case 6:
                cout << "Ingrese valor a buscar: ";
                cin >> valor;
                buscarElemento(valor);
                break;
            case 7:
                vaciarPila();
                break;
            case 8:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 8);
}

int main() {
    menu();
    return 0;
}