// Trayectoria de Proyectiles

#include <iostream>
#include <string>
#include <cmath>

float validarIngreso(const std::string mensaje) {
    float valor;

    while (true) {
        std::string input;
        std::cout << " > Ingrese " << mensaje << ": "; std::cin >> input;

        try {
            valor = std::stof(input);
            if (valor <= 0) throw std::invalid_argument("");
            return valor;
        } catch (...) {
            for (int i = 0; i < 13 + mensaje.length(); i++) std::cout << " "; // Coloca un mensaje de error intuitivo
            std::cout << "^ Error: ingreso invalido.\n\n";
        }
    }
}

int main() {
    float H = validarIngreso("la altura (m) del muro");
    float D = validarIngreso("la distancia (m) al muro");
    float v = validarIngreso("la velocidad (m/s) del objeto");
    float t = validarIngreso("el angulo (grados) del tiro") * (3.1415 / 180.0f);

    // Ecuación de un proyectil
    float resultado = D * tanf(t) - 
        (9.81f * (D * D)) /
        (2 * (v * v) * (cosf(t) * cosf(t)));

    std::cout << "  << El proyectil va a ";
    if (resultado < H) {
        std::cout << "chocar contra";
    } else if (resultado = H) {
        std::cout << "rozar";
    } else std::cout << "superar";
    std::cout << " el muro.\n" << std::endl;

    return 0;
}
