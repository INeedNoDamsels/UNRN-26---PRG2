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
    std::cout << "\n     Lista Simple Enlazada\n"
              << "\n<1> Mostrar todos los elementos\n     <2> Insertar elemento\n      <3> Borrar elemento\n\t   <0> Salir\n" << std::endl;
}

bool ingresoValido(const std::string& cadena) {
    if (cadena.empty()) return false;

    int i = 0;

    if (cadena[0] == '-') {
        if (cadena.length() == 1) return false;
        i = 1;
    }

    for (; i < cadena.length(); i++) if (!std::isdigit(cadena[i])) return false;

    return true;
}

int ingresarValor(const std::string& mensaje, int min, int max) {
    int valor;

    while (true) {
        std::string input;

        std::cout << mensaje; std::cin >> input;

        try {
            if (!ingresoValido(input)) throw std::invalid_argument("valor no entero.");

            valor = std::stoi(input);

            if (valor < min || valor > max) throw std::invalid_argument("valor fuera de rango.");

            return valor;

        } catch (const std::exception& exc) {
            for (int i = 0; i < mensaje.length(); i++) std::cout << " ";
            std::cout << "^ Aviso: " << exc.what() << std::endl;
        }
    }
}

void mostrarMensaje(bool exito, const std::string& mensajeExito, const std::string& mensajeError) {
    if (exito) {
        std::cout << mensajeExito << std::endl;
    } else std::cout << mensajeError << std::endl;
}

// ===== PROGRAMA PRINCIPAL ===============================
int main() {
    Lista lista;
    bool continuar = true;

    while (continuar) {
        menu();

        int opcion = ingresarValor(" > Seleccione operacion: ", 0, 4);

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
                int valor = ingresarValor(" > Ingrese valor entero a insertar: ", std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                mostrarMensaje(lista.insertarOrdenado(valor), " < Valor insertado exitosamente.", " < Error al intentar insertar.");
                break;
            }

            case 3: {
                int valor = ingresarValor(" > Ingrese valor a borrar: ", std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                mostrarMensaje(lista.borrarElemento(valor), " < Valor borrado exitosamente.", " < Error al intentar borrar.");
                break;
            }

            default:
                break;
        }
    }

    return 0;
}