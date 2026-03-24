// Optimización de Stock

#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <chrono>

int ingresar() {
    int valor;

    while (true) {
        std::string input;

        std::cout << "<1> Actualizar stock <2> Realizar pedido\n\t\t<Otro> Vender\n\t\t  <3> Salir" << std::endl;
        std::cout << "\n > Ingrese opcion: "; std::cin >> input;

        try {
            valor = std::stoi(input);
            if (valor <= 0) throw std::invalid_argument("");
            return valor;
        } catch (...) {
            for (int i = 0; i < 19 ; i++) std::cout << " ";
            std::cout << "^ Error: ingreso invalido.\n" << std::endl;
        }
    }
}
void lapso(int segundos) {
    for (int i = 0; i < segundos; i++) {
        std::cout << ".";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::endl << std::endl;
}
int obtener(int min, int max) {
    static std::random_device semilla;
    static std::mt19937 valor(semilla());
    std::uniform_int_distribution<> generador(min, max);

    return generador(valor);
}

class Producto {
public:
    std::string nombre;
    float precioUnitario;

    Producto(std::string n, float p) : nombre(n), precioUnitario(p) {}
};
class Inventario {
public:
    Producto producto;
    int cantidad, puntoCritico;

    Inventario(const Producto& p, int c, int pc) : producto(p), cantidad(c), puntoCritico(pc) {}

    bool necesitaReposicion() const {
        return cantidad <= puntoCritico;
    }

    void mostrar() const {
        std::cout << " < " << producto.nombre << ", quedan: " << cantidad;

        if (necesitaReposicion()) std::cout << ". Necesita reposicion.";

        std::cout << std::endl;
    }

    float reponer(int cantidad) {
        this->cantidad += cantidad;

        float costo = 100.0f;
        if (cantidad > 50) {
            costo = 0.0f;
            std::cout << " < Costo fijo bonificado." << std::endl;
        }

        return costo + (cantidad * producto.precioUnitario);
    }
};
class Negocio {
public:
    float saldo;
    float deuda;
    Inventario items[3];

    Negocio(float s, Inventario* i) : saldo(s), deuda(0.0f), items{i[0], i[1], i[2]} {}

    void vender() {
    int i = obtener(0, 2);

    if (items[i].cantidad > 0) {
        int vendidas = obtener(1, items[i].cantidad);

        float precioVenta = items[i].producto.precioUnitario * 1.3f;
        float ganancia = vendidas * precioVenta;

        items[i].cantidad -= vendidas;

        std::cout << " > Vendiste " << vendidas << " de " << items[i].producto.nombre << " | Ganancia: $" << ganancia << std::endl;

        if (deuda > 0) {
            if (ganancia >= deuda) {
                ganancia -= deuda;
                deuda = 0;
                saldo += ganancia;
            } else {
                deuda -= ganancia;
            }
        } else saldo += ganancia;
    } else std::cout << " < No hay stock para vender." << std::endl;
}

    void mostrarStock() const {
        std::cout << "[Saldo: $" << saldo << " | Deuda: $" << deuda << "]" << std::endl;

        for (int i = 0; i < 3; i++) items[i].mostrar();
    }

    void realizarPedido() {
        float total = 0;

        for (int i = 0; i < 3; i++) {
            if (items[i].necesitaReposicion()) {
                int cantidad = obtener(30, 60);
                total += items[i].reponer(cantidad);
            }
        }

        std::cout << " < Costo total: $" << total << std::endl;

        saldo -= total;

        if (saldo < 0) {
            deuda += -saldo;
            saldo = 0;
        }
    }
};

int main() {
    bool bandera = true;

    Producto productos[3] = {
        {"Pan", 9.5f},
        {"Leche", 14.6f},
        {"Huevos", 18.0f}
    };
    Inventario items[3] = {
        {productos[0], obtener(5, 30), 4},
        {productos[1], obtener(5, 30), 4},
        {productos[2], obtener(5, 30), 4}
    };
    Negocio miNegocio(100.0f, items);

    while (bandera) {
        std::cout << "\n      - Programa de gestion de stock -" << std::endl;
        switch (ingresar()) {
            case 1:
                std::cout << " < Revisando stock"; lapso(3);
                miNegocio.mostrarStock();
                break;

            case 2:
                std::cout << " < Realizando pedido"; lapso(3);
                miNegocio.realizarPedido();
                break;

            case 3:
                std::cout << " < Cerrando sesion"; lapso(3);
                bandera = false;
                break;

            default:
                std::cout << " < Atendiendo clientes"; lapso(3);
                if (obtener(1, 9) % 2 == 0) miNegocio.vender();
                break;
        }
    }

    return 0;
}
