// Optimización de Stock

#include <iostream>
#include <string>

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
    Producto pan("Pan (1kg)", 12);
    Producto leche("Leche (1L)", 30);
    Producto huevo("Maple de huevos", 40);

    Inventario item1(pan, 10, 5);
    Inventario item2(leche, 10, 5);
    Inventario item3(huevo, 10, 5);

    float cFijo = 100.0f;

    std::cout << "\nProducto: " << item1.producto.nombre << "\n  Quedan " << item1.cantidad;
    std::cout << "\nProducto: " << item2.producto.nombre << "\n  Quedan " << item2.cantidad;
    std::cout << "\nProducto: " << item3.producto.nombre << "\n  Quedan " << item3.cantidad;
    std::cout << std::endl;

    float costo = reponerStock(item1, 60, cFijo);

    std::cout << "\n > Costo del pedido: $" << costo << std::endl;
    std::cout << "  >> Nuevo stock: " << item1.cantidad << std::endl;

    return 0;
}
