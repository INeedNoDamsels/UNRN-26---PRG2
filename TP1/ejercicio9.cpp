// Geofencing

#include <iostream>
#include <random>
#include <cmath>

struct Dron {
    int p_x, p_y;

    Dron(int a, int b) : p_x(a), p_y(b) {}
};
struct Area {
    int x_1, x_2, y_1, y_2;

    Area(int a, int b, int c, int d) {
        x_1 = std::min(a, b);
        x_2 = std::max(a, b);
        y_1 = std::min(c, d);
        y_2 = std::max(c, d);
    }

    bool tieneA(const Dron& dron) const {
        return (dron.p_x >= x_1 && dron.p_x <= x_2) && (dron.p_y >= y_1 && dron.p_y <= y_2);
    }

    void imprimirse(const Dron& dron) const {
        int ancho = std::abs(x_2 - x_1) + 1;
        int alto  = std::abs(y_2 - y_1) + 1;

        for (int i = alto - 1; i >= 0; i--) {
            std::cout << "|";
            for (int j = 0; j < ancho; j++) {
                int x_actual = x_1 + j;
                int y_actual = y_1 + i;

                std::cout << ((dron.p_x == x_actual && dron.p_y == y_actual) ? "X" : " ");
            }
            std::cout << "|\n";
        }
    }
};

int obtener(int min, int max) {
    static std::random_device semilla;
    static std::mt19937 valor(semilla());
    std::uniform_int_distribution<> generador(min, max);

    return generador(valor);
}

int main() {
    int x1 = obtener(10, 25);
    int y1 = obtener(10, 25);

    int ancho = obtener(3, 8);
    int alto  = obtener(3, 8);

    int x2 = x1 + ancho;
    int y2 = y1 + alto;

    Area rectangulo(x1, x2, y1, y2);
    Dron miDroncito(
        obtener(x1 - 2, x2 + 2),
        obtener(y1 - 2, y2 + 2)
    );

    std::cout << "Se ha generado un area de ["
              << (x2 - x1 + 1) << " x "
              << (y2 - y1 + 1) << "]:\n";
    rectangulo.imprimirse(miDroncito);

    std::cout << (rectangulo.tieneA(miDroncito) ? "\n < Dron localizado." : "\n < Alerta! No hay rastro del dron.") << std::endl;

    return 0;
}