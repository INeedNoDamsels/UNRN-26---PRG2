// Reserva de Butacas

#include <iostream>
#include <string>
#include <random>
#include <tuple>

const int FILAS    = 9;
const int COLUMNAS = 32;

int obtener() {
    static std::random_device semilla;
    static std::mt19937 valor(semilla());
    std::uniform_int_distribution<> generador(0, 1);

    return generador(valor);
}

int ingresar(const std::string mensaje) {
    while (true) {
        std::string input;
        std::cout << "\n > Ingrese " << mensaje << ": "; std::cin >> input;

        try {
            int valor = stoi(input);
            if (valor <= 0 || valor > COLUMNAS) throw std::out_of_range("");
            return valor;
        } catch (std::out_of_range) {
            for (int i = 0; i < 13 + mensaje.length(); i++) std::cout << " ";
            std::cout << "^ Aviso: debe ingresar un valor entre 1 y " << COLUMNAS << ".\n";
        } catch (...) {
            for (int i = 0; i < 13 + mensaje.length(); i++) std::cout << " ";
            std::cout << "^ Error: ingreso invalido.\n";
        }
    }
}

void mostrar(int sala[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        std::cout << i + 1 << ": ";
        for (int j = 0; j < COLUMNAS; j++) {
            if (sala[i][j] == 2) {
                std::cout << "[x]";
            } else std::cout << "[" << (sala[i][j] ? "o" : " ") << "]";
        }
        std::cout << "\n";
    }
}

std::tuple<int, int> buscarButaca(int sala[FILAS][COLUMNAS], int cantidad) {
    int contador = 0;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            (!sala[i][j]) ? contador++ : contador = 0;

            if (contador == cantidad) return {i, j - cantidad + 1};
        }
    }

    return {-1, -1};
}

int main() {
    int sala[FILAS][COLUMNAS];

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) sala[i][j] = obtener();
    }

    mostrar(sala);

    while (true) {
        int cantidad = ingresar("cantidad de personas");
        auto [f, c]  = buscarButaca(sala, cantidad);

        if (f != -1 && c != -1) {
            std::cout << " < Butacas encontradas en la fila " << f + 1 << ", columna " << c + 1 << ".\n";
            for (int i = c; i < c + cantidad; i++) sala[f][i] = 2;
            mostrar(sala);
        } else if (cantidad == 1 && (f == -1 || c == -1)) {
            std::cout << " < No quedan butacas disponibles.\n" << std::endl;
            break;
        } else std::cout << " < No se encontraron " << cantidad << " butacas consecutivas disponibles.\n";
    }

    return 0;
}
