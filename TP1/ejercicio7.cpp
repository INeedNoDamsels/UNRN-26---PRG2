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

float reponerStock(Inventario& inventario, unsigned cantidad, float costo) {
    if (!inventario.necesitaReposicion()) {
        std::cout << "\n  << No se necesita reposicion.\n";
        return 0.0f;
    }

    inventario.cantidad += cantidad;

    if (cantidad > 50) costo = 0.0f;

    return costo + (cantidad * inventario.producto.precioUnitario);
}

int main() {
    std::random_device semilla;
    std::mt19937 valor(semilla());
    std::uniform_int_distribution<int> obtener(5, 40);

    Producto productos[3] = {
        Producto("Pan", 9.5f),
        Producto("Leche", 28.6f),
        Producto("Huevos", 32.0f)
    };

    Inventario items[3] = {
        Inventario(productos[0], obtener(valor), 4),
        Inventario(productos[1], obtener(valor), 4),
        Inventario(productos[2], obtener(valor), 4)
    };

    while(true) {
        for(int i = 0; i < 3; i++) {
            std::cout << items[i].producto.nombre << ": " << items[i].cantidad << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
