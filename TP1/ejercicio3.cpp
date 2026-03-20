// Control de Calidad

#include <iostream>
#include <random>
#include <cmath>

const float MIN = 13.5;
const float MAX = 16.5;

const int MEDIDAS  = 3;   // Medidas de cada pieza
const int CANTIDAD = 300; // Cantidad de piezas pertenecientes al lote generado.

int main() {
    bool esValido;
    float  piezas[CANTIDAD][MEDIDAS];

    std::random_device semilla;
    std::mt19937 valor(semilla());
    std::normal_distribution<> obtener(15.0, 0.5);

    // Generador de diámetros para cada pieza fabricada
    for(int i = 0; i < CANTIDAD; i++) {
        for(int j = 0; j < MEDIDAS; j++) piezas[i][j] = round(obtener(valor) * 100) / 100;
    }

    // Ciclo que obtiene el promedio del lote
    float promedio = 0.0;
    for(int i = 0; i < CANTIDAD; i++) {
        for(int j = 0; j < MEDIDAS; j++) promedio += piezas[i][j];
    }
    promedio /= (CANTIDAD * MEDIDAS);
    esValido = (promedio >= MIN && promedio <= MAX);

    // Ciclo que evalúa la desviación de cada pieza del lote
    for(int i = 0; i < CANTIDAD; i++) {
        for(int j = 0; j < MEDIDAS; j++) {
            float desviacion = fabs(piezas[i][j] - promedio);

            if (desviacion > (0.10 * promedio)) {
                esValido = false;
                break;
            }
        }
    }

    std::cout << "\n < El lote de " << CANTIDAD << " piezas es considerado \"";
    esValido ? (std::cout << "aceptable") : (std::cout << "no aceptable");
    std::cout << "\".\n" << std::endl;

    return 0;
}
