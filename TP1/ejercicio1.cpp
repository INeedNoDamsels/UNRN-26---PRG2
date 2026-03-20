// El Costo de la Infraestructura

#include <iostream>
#include <cmath>

const int costos[2] = {10, 13}; // Elegí cambiar el valor del cableado por diagonal para que sea más variantes los resultados

float ingresar(const std::string mensaje) {
    float valor;

    while (true) {
        std::string input;
        std::cout << " > Ingrese el " << mensaje << " (m) del terreno: "; std::cin >> input;

        try {
            valor = std::stof(input);
            if (valor <= 0) throw std::invalid_argument("");
            return valor;
        } catch (...) {
            for (int i = 0; i < 37; i++) std::cout << " "; // Coloca un mensaje de error intuitivo
            std::cout << "^ Error: ingreso invalido.\n\n";
        }
    }
}

int main(int argc, char* argv[]) {
    float terreno[2];
    float valores[2];
    bool bandera = false;

    if (argc == 3) {
        try {
            terreno[0] = std::stof(argv[1]);
            terreno[1] = std::stof(argv[2]);
            std::cout << " < Medidas del terreno recibidas como parametros.\n";
            bandera = true;
        } catch (...) {}
    }

    if (!bandera) {
        terreno[0] = ingresar("ancho");
        terreno[1] = ingresar("largo");
    }

    valores[0] = costos[0] * (terreno[0] + terreno[1]);
    valores[1] = costos[1] * sqrt(pow(terreno[0], 2) + pow(terreno[1], 2));

    std::cout << "  << Es conveniente cablear "
              << (valores[0] < valores[1] ? "por el borde" : "en diagonal");
    std::cout << ".\n" << std::endl;

    return 0;
}
