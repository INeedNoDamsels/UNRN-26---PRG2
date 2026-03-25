#include <iostream>
#include <random>
#include <thread>
#include <chrono>

int obtener() {
    static std::random_device semilla;
    static std::mt19937 valor(semilla());
    std::uniform_int_distribution<> generador(0, 1);

    return generador(valor);
}
void lapso(int segundos) {
    std::this_thread::sleep_for(std::chrono::seconds(segundos));
}

int main() {
    bool fila[10];

    for (int i = 0; i < 10; i++) fila[i] = obtener();

    while (true) {
        for (int i = 0; i < 10; i++) {
            std::cout << "[";
            fila[i] ? std::cout << "█" : std::cout << " ";
            std::cout << "]";
        }
        
        std::cout << std::endl;
        lapso(1);

        bool nueva[10];

        for (int i = 1; i < 9; i++) nueva[i] = (fila[i - 1] == fila[i + 1]);

        for (int i = 1; i < 9; i++) fila[i] = nueva[i];
    }

    return 0;
}
