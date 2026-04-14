// 3. Clases con Memoria Dinámica

#include <iostream>
#include <vector>
#include <limits>

// ===== ESTRUCTURAS ======================================
struct Nodo {
    int dato;
    Nodo* siguiente;

    Nodo(int d) : dato(d), siguiente(nullptr) {}
};

class Lista {
private:
    Nodo* cabeza;

public:
    Lista() : cabeza(nullptr) {}
    ~Lista() {
        Nodo* actual = cabeza;

        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;

            delete actual;
            actual = siguiente;
        }
    }

    bool insertarAlComienzo(int valor) {
        Nodo* nuevo = new Nodo(valor);

        nuevo->siguiente = cabeza;
        cabeza = nuevo;

        return true;
    }

    /**
     * @brief Devuelve un vector con los elementos de la lista en orden. Se recorre la lista desde la cabeza hasta el final, agregando cada dato al vector. Si la lista está vacía, se devuelve un vector vacío.
     * Mi reversión del método 'mostrar' solicitado que separa la lógica de la presentación, me parece es más "limpio".
     * 
     * @return Un vector que contiene los elementos de la lista en orden.
     */
    std::vector<int> obtenerElementos() const {
        std::vector<int> elementos;
        Nodo* actual = this->cabeza;

        while (actual != nullptr) {
            elementos.push_back(actual->dato);
            actual = actual->siguiente;
        }

        return elementos;
    }

    bool insertarAlFinal(int valor) {
        Nodo* nuevo = new Nodo(valor);

        if (cabeza == nullptr) {
            cabeza = nuevo;
            return true;
        }

        Nodo* actual = cabeza;

        while (actual->siguiente != nullptr) actual = actual->siguiente;

        actual->siguiente = nuevo;

        return true;
    }

    bool insertarOrdenado(int valor) {
        Nodo* nuevo = new Nodo(valor);

        if (cabeza == nullptr || valor < cabeza->dato) {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;

            return true;
        }

        Nodo* actual = cabeza;

        while (actual->siguiente != nullptr && actual->siguiente->dato < valor) actual = actual->siguiente;

        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;

        return true;
    }

    bool borrarElemento(int valor) {
        if (cabeza == nullptr) return false;

        if (cabeza->dato == valor) {
            Nodo* temporal = cabeza;

            cabeza = cabeza->siguiente;
            delete temporal;

            return true;
        }

        Nodo* actual = cabeza;

        while (actual->siguiente != nullptr && actual->siguiente->dato != valor) actual = actual->siguiente;

        if (actual->siguiente != nullptr) {
            Nodo* temporal = actual->siguiente;

            actual->siguiente = actual->siguiente->siguiente;
            delete temporal;

            return true;
        }

        return false;
    }
};

// ===== UTILS ============================================
void menu() {
    std::cout << "\n\t     Lista Simple Enlazada\n"
              << "\n\t<1> Mostrar todos los elementos\n<2> Insertar al principio <3> Insertar al final\n\t  <4> Borrar elemento <0> Salir" << std::endl;
}

int ingresarValor(const std::string& mensaje, int min, int max) {
    int valor;

    while (true) {
        std::string input;

        std::cout << mensaje; std::cin >> input;

        try {
            valor = std::stoi(input);
            if (valor < min || valor > max) throw std::invalid_argument("");

            return valor;
        } catch (...) {
            for (int i = 1; i < mensaje.length(); i++) std::cout << " ";
            std::cout << "^ Aviso: opcion invalida." << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void mostrarMensaje(bool exito, const std::string& mensajeExito, const std::string& mensajeError) {
    if (exito) {
        std::cout << "\n" << mensajeExito << std::endl;
    } else std::cout << "\n" << mensajeError << std::endl;
}

// ===== PROGRAMA PRINCIPAL ===============================
int main() {
    Lista lista;
    bool continuar = true;

    while (continuar) {
        menu();

        int opcion = ingresarValor("\n > Seleccione operacion: ", 0, 4);

        switch (opcion) {
            case 0: {
                continuar = false;
                break;
            }

            case 1: {
                std::vector<int> elementos = lista.obtenerElementos();

                if (elementos.empty()) {
                    std::cout << " < La lista esta vacia." << std::endl;
                } else {
                    std::cout << " < Elementos de la lista: [";
                    for (int elem : elementos) std::cout << elem << "]" << (elem == elementos.back() ? "" : ", [");
                    std::cout << std::endl;
                }
                break;
            }

            case 2: {
                int valor = ingresarValor(" > Ingrese valor a insertar al principio: ", std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                mostrarMensaje(lista.insertarAlComienzo(valor), " < Valor insertado exitosamente.", " < Error al insertar valor.");
                break;
            }

            case 3: {
                int valor = ingresarValor(" > Ingrese valor a insertar al final: ", std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                mostrarMensaje(lista.insertarAlFinal(valor), " < Valor insertado exitosamente.", " < Error al insertar valor.");
                break;
            }

            case 4: {
                int valor = ingresarValor(" > Ingrese valor a borrar: ", std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                mostrarMensaje(lista.borrarElemento(valor), " < Valor borrado exitosamente.", " < Error al borrar valor.");
                break;
            }

            default:
                break;
        }
    }

    return 0;
}