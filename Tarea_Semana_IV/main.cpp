#include <iostream>
#include <string>

using namespace std;

// Estructura Producto
struct Producto {
    int codigo;
    string nombre;
    double precio;
};

// Estructura Nodo
struct Nodo {
    Producto producto;
    Nodo* siguiente;
};

int main() {

    cout << "Nombre: Alex Velasquez" << endl << endl;

    Nodo* cabeza = NULL;
    Nodo* nuevo = NULL;
    Nodo* auxiliar = NULL;

    // Crear 4 nodos
    for (int i = 0; i < 4; i++) {

        nuevo = new Nodo;          // Crear nodo dinámicamente
        nuevo->siguiente = NULL;   // Inicializar siguiente en NULL

        cout << "Producto " << i + 1 << endl;

        cout << "Codigo: ";
        cin >> nuevo->producto.codigo;

        cout << "Nombre: ";
        cin >> nuevo->producto.nombre;   // Simple para principiante (sin espacios)

        cout << "Precio: ";
        cin >> nuevo->producto.precio;

        cout << "---------------------" << endl;

        // Insertar en la lista
        if (cabeza == NULL) {
            cabeza = nuevo;
        } else {
            auxiliar = cabeza;
            while (auxiliar->siguiente != NULL) {
                auxiliar = auxiliar->siguiente;
            }
            auxiliar->siguiente = nuevo;
        }
    }

    cout << endl << "=== Lista de Productos ===" << endl;

    double total = 0;

    auxiliar = cabeza;
    while (auxiliar != NULL) {

        cout << "Codigo: " << auxiliar->producto.codigo << endl;
        cout << "Nombre: " << auxiliar->producto.nombre << endl;
        cout << "Precio: Q" << auxiliar->producto.precio << endl;
        cout << "---------------------" << endl;

        total = total + auxiliar->producto.precio;

        auxiliar = auxiliar->siguiente;
    }

    cout << "Total acumulado: Q" << total << endl;

    // Liberar memoria
    auxiliar = cabeza;
    while (auxiliar != NULL) {
        Nodo* temp = auxiliar;
        auxiliar = auxiliar->siguiente;
        delete temp;
    }

    return 0;
}