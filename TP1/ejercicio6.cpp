// Sensor de Estabilidad

#include <iostream>
#include <random>
#include <cmath>

const int VALORES = 15; // Cantidad de valores pertenecientes a la lista entregada por el sensor

float redondear(float valor) {
    return std::round(valor * 100) / 100;
}

int limpiar(float* arreglo, int longitud, float* salida) {
    int j = 0;

    for (int i = 0; i < longitud; i++) {
        if (arreglo[i] >= 0) {
            salida[j] = arreglo[i];
            j++;
        }
    }

    return j;
}

float promediar(float* arreglo, int longitud) {
    if (longitud == 0) return 0;

    float promedio = 0.0;
    for (int i = 0; i < longitud; i++) promedio += arreglo[i];

    return redondear(promedio / longitud);
}

int main() {
    float lista[VALORES], nuevo[VALORES];

    std::random_device semilla;
    std::mt19937 valor(semilla());
    std::uniform_real_distribution<float> obtener(-9.99f, 45.0f);

    for (int i = 0; i < VALORES; i++) lista[i] = redondear(obtener(valor));

    std::cout << "\n < El sensor de presion ha detectado los siguientes valores: \n\t";
    for (float elemento : lista) std::cout << " [" << elemento << "]";

    int cantidad = limpiar(lista, VALORES, nuevo);
    std::cout << "\n\n  << Se han eliminado " << VALORES - cantidad << " elementos.\n";

    if (cantidad > 0) {
        std::cout << "  << El sensor de presion ha detectado un promedio de " << promediar(nuevo, cantidad) << " Pa de presion.\n";
    } else std::cout << "  << No hay valores validos para calcular el promedio.\n";
    std::cout << std::endl;

    return 0;
}
