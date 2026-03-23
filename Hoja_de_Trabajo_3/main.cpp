#include <iostream>
using namespace std;

struct Nodo {
    int carne;
    char nombre[50];
    char apellido[50];
    char carrera[50];
    Nodo* siguiente;
};

// Insertar al inicio
void insertarInicio(Nodo*& head) {
    Nodo* nuevo = new Nodo();

    cout << "Carne: ";
    cin >> nuevo->carne;
    cin.ignore(1000, '\n');

    cout << "Nombre: ";
    cin >> nuevo->nombre;

    cout << "Apellido: ";
    cin >> nuevo->apellido;

    cout << "Carrera: ";
    cin >> nuevo->carrera;

    nuevo->siguiente = head;
    head = nuevo;

    cout << "Estudiante agregado al inicio.\n";
}

// Insertar al final
void insertarFinal(Nodo*& head) {
    Nodo* nuevo = new Nodo();

    cout << "Carne: ";
    cin >> nuevo->carne;
    cin.ignore(1000, '\n');

    cout << "Nombre: ";
    cin >> nuevo->nombre;

    cout << "Apellido: ";
    cin >> nuevo->apellido;

    cout << "Carrera: ";
    cin >> nuevo->carrera;

    nuevo->siguiente = NULL;

    if (head == NULL) {
        head = nuevo;
    } else {
        Nodo* temp = head;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }

    cout << "Estudiante agregado al final.\n";
}

// Mostrar
void mostrar(Nodo* head) {
    if (head == NULL) {
        cout << "Lista vacia.\n";
        return;
    }

    Nodo* temp = head;
    while (temp != NULL) {
        cout << "Carne: " << temp->carne << endl;
        cout << "Nombre: " << temp->nombre << endl;
        cout << "Apellido: " << temp->apellido << endl;
        cout << "Carrera: " << temp->carrera << endl;
        cout << "----------------------\n";
        temp = temp->siguiente;
    }
}

// Buscar
void buscar(Nodo* head) {
    int carne;
    cout << "Ingrese carne a buscar: ";
    cin >> carne;

    Nodo* temp = head;
    while (temp != NULL) {
        if (temp->carne == carne) {
            cout << "Estudiante encontrado:\n";
            cout << "Nombre: " << temp->nombre << endl;
            cout << "Apellido: " << temp->apellido << endl;
            cout << "Carrera: " << temp->carrera << endl;
            return;
        }
        temp = temp->siguiente;
    }

    cout << "Estudiante no encontrado.\n";
}

// Eliminar
void eliminar(Nodo*& head) {
    int carne;
    cout << "Ingrese carne a eliminar: ";
    cin >> carne;

    Nodo* temp = head;
    Nodo* anterior = NULL;

    while (temp != NULL && temp->carne != carne) {
        anterior = temp;
        temp = temp->siguiente;
    }

    if (temp == NULL) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    if (anterior == NULL) {
        head = temp->siguiente;
    } else {
        anterior->siguiente = temp->siguiente;
    }

    delete temp;
    cout << "Estudiante eliminado.\n";
}

// MAIN
int main() {
    Nodo* head = NULL;
    int opcion;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Insertar al inicio\n";
        cout << "2. Insertar al final\n";
        cout << "3. Mostrar estudiantes\n";
        cout << "4. Buscar estudiante\n";
        cout << "5. Eliminar estudiante\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                insertarInicio(head);
                break;
            case 2:
                insertarFinal(head);
                break;
            case 3:
                mostrar(head);
                break;
            case 4:
                buscar(head);
                break;
            case 5:
                eliminar(head);
                break;
            case 6:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 6);

    return 0;
}