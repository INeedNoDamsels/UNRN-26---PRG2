// Optimización de Stock

#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <chrono>

class Producto {
public:
    std::string nombre;
    float precioUnitario;

    Producto(std::string n, float p) : nombre(n), precioUnitario(p) {}
};

class Inventario {
public:
    Producto producto;
    unsigned cantidad, puntoCritico;

    Inventario(const Producto& p, unsigned c, unsigned pc) : producto(p), cantidad(c), puntoCritico(pc) {}

    bool necesitaReposicion() const {
        return cantidad <= puntoCritico;
    }
};

void actualizarStock(Inventario& inventario) {
    std::cout << " < " << inventario.producto.nombre << ", quedan: " << inventario.cantidad;

    if (!inventario.necesitaReposicion()) std::cout << ". No necesita reposicion." << std::endl;
}

float reponerStock(Inventario& inventario, unsigned cantidad, float costo) {
    inventario.cantidad += cantidad;

    if (cantidad > 50) costo = 0.0f;

    return costo + (cantidad * inventario.producto.precioUnitario);
}

int obtener(int min, int max) {
    static std::random_device semilla;
    static std::mt19937 valor(semilla());
    std::uniform_int_distribution<> generador(min, max);

    return generador(valor);
}

void lapso(int segundos) {
    for (int i = 0; i < segundos; i++) {
        std::cout << ".";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::endl << std::endl;
}

int ingresar() {
    int valor;

    while (true) {
        std::string input;
        std::cout << "<1> Actualizar stock " << "<2> Realizar pedido" << "\n\t<3> Salir" << std::endl;
        std::cout << "\n > Ingrese opcion: "; std::cin >> input;

        try {
            valor = std::stoi(input);
            if (valor <= 0) throw std::invalid_argument("");
            return valor;
        } catch (...) {
            for (int i = 0; i < 19; i++) std::cout << " ";
            std::cout << "^ Error: ingreso invalido.\n\n";
        }
    }
}

int main() {
    Producto productos[3] = {
        Producto("Pan", 9.5f),
        Producto("Leche", 14.6f),
        Producto("Huevos", 18.0f)
    };

    Inventario items[3] = {
        Inventario(productos[0], obtener(5 ,30), 4),
        Inventario(productos[1], obtener(5, 30), 4),
        Inventario(productos[2], obtener(5, 30), 4)
    };

    while (true) {
        std::cout << "\n - Programa de gestion de stock -" << std::endl;
        switch (ingresar()) {
            case 1:
                std::cout << "  < Revisando stock"; lapso(3);
                for (int i = 0; i < 3; i++) actualizarStock(items[i]);
                break;

            case 2:
                std::cout << "  < Realizando pedido"; lapso(3);
                for (int i = 0; i < 3; i++) reponerStock(items[i], obtener(30, 60), items[i].producto.precioUnitario);
                break;

            default:
                //
                break;
        }
    }

    return 0;
}
