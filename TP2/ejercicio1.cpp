// 1. Clases Simples

#include <iostream>
#include <random>
#include <cmath>

float MIN = -10.0f;
float MAX =  10.0f;

float obtener(float MIN, float MAX) {
    static std::random_device semilla;
    static std::mt19937 valor(semilla());
    std::uniform_real_distribution<float> generador(MIN, MAX);

    return round(generador(valor) * 100.0f) / 100.0f;
}

class Intervalo {
public:
    float extremoInferior, extremoSuperior;
    bool inferiorInclusivo, superiorInclusivo;

    Intervalo(float ei, bool ii, float es, bool si) {
        if (ei <= es) {
            extremoInferior = ei;
            extremoSuperior = es;
            inferiorInclusivo = ii;
            superiorInclusivo = si;
        } else {
            extremoInferior = es;
            extremoSuperior = ei;
            inferiorInclusivo = si;
            superiorInclusivo = ii;
        }
    }

    bool limiteInferior() const { return inferiorInclusivo; }
    bool limiteSuperior() const { return superiorInclusivo; }

    bool contiene(float valor) const {
        bool cumpleInferior = inferiorInclusivo ? (valor >= extremoInferior) : (valor > extremoInferior);
        bool cumpleSuperior = superiorInclusivo ? (valor <= extremoSuperior) : (valor < extremoSuperior);

        return cumpleInferior && cumpleSuperior;
    }

    bool esIgualQue(const Intervalo& otro) const {
        return (extremoInferior == otro.extremoInferior)
            && (extremoSuperior == otro.extremoSuperior)
            && (inferiorInclusivo == otro.inferiorInclusivo)
            && (superiorInclusivo == otro.superiorInclusivo);
    }

    bool seSuperponeCon(const Intervalo& otro) const {
        if (extremoSuperior < otro.extremoInferior || otro.extremoSuperior < extremoInferior) {
            return false; // No se superponen
        } else if (extremoSuperior == otro.extremoInferior) {
            return superiorInclusivo && otro.inferiorInclusivo; // Se superponen solo si ambos son inclusivos
        } else if (otro.extremoSuperior == extremoInferior) {
            return otro.superiorInclusivo && inferiorInclusivo; // Se superponen solo si ambos son inclusivos
        } else return true; // Se superponen
    }

    bool estaContenidoEn(const Intervalo& otro) const {
    if (extremoInferior < otro.extremoInferior) return false;
    if (extremoInferior == otro.extremoInferior) {
        if (inferiorInclusivo && !otro.inferiorInclusivo) return false;
    }

    if (extremoSuperior > otro.extremoSuperior) return false;
    if (extremoSuperior == otro.extremoSuperior) {
        if (superiorInclusivo && !otro.superiorInclusivo) return false;
    }

    return true;
}
};

int main () {
    float valor = obtener(MIN, MAX);

    Intervalo intervalo1(obtener(MIN, MAX), true, obtener(MIN, MAX), false);
    Intervalo intervalo2(obtener(MIN, MAX), false, obtener(MIN, MAX), true);

    std::cout << "\n\tIntervalo 1: "
        << (intervalo1.limiteInferior() ? "[" : "(") << intervalo1.extremoInferior << ", " << intervalo1.extremoSuperior
        << (intervalo1.limiteSuperior() ? "]" : ")") << std::endl;

    std::cout << "\tIntervalo 2: "
        << (intervalo2.limiteInferior() ? "[" : "(") << intervalo2.extremoInferior << ", " << intervalo2.extremoSuperior
        << (intervalo2.limiteSuperior() ? "]" : ")") << std::endl;

    std::cout << "\n1: > Se encuentra el numero '" << valor << "' dentro de uno de los intervalos?"
        << (intervalo1.contiene(valor) || intervalo2.contiene(valor) ? "\n  < Si" : "\n  < No") << std::endl;
    std::cout << "2: > Son los intervalos iguales? "<< (intervalo1.esIgualQue(intervalo2) ? "\n  < Si" : "\n  < No") << std::endl;
    std::cout << "3: > Se superponen los intervalos? " << (intervalo1.seSuperponeCon(intervalo2) ? "\n  < Si" : "\n  < No") << std::endl;
    std::cout << "4: > Se encuentra contenido intervalo 1 en el intervalo 2? " << (intervalo1.estaContenidoEn(intervalo2) ? "\n  < Si" : "\n  < No") << std::endl;

    return 0;
}