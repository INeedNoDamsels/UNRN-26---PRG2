// El Costo de la Infraestructura

#include <iostream>
#include <cmath>

const int costos[2] = {10, 13};

int main(int argc, char* argv[]) {
    float terreno[2];
    float valores[2];

    if (argc != 3) {
        std::cout << " > Ingrese el ancho en metros del terreno: "; std::cin >> terreno[0];
        std::cout << " > Ingrese el largo en metros del terreno: "; std::cin >> terreno[1];
    } else {
        terreno[0] = atoi(argv[1]);
        terreno[1] = atoi(argv[2]);
    }

    valores[0] = costos[0] * (terreno[0] + terreno[1]);
    valores[1] = costos[1] * sqrt(pow(terreno[0], 2) + pow(terreno[1], 2));

    std::cout << " < La opcion mas economica seria cablear ";
    std::cout << (valores[0] < valores[1] ? "por el borde.\n" : "en diagonal.\n");

    return 0;
}
