// El Dígito Verificador

#include <iostream>
#include <string>

std::string ingresar(const std::string mensaje) {
    float valor;

    while (true) {
        std::string input;
        std::cout << "\n > Ingrese " << mensaje << ": "; std::cin >> input;

        try {
            if (input.length() != 5 || std::stof(input) <= 0) throw std::invalid_argument("");
            return input;
        } catch (...) {
            for (int i = 0; i < 13 + mensaje.length(); i++) std::cout << " "; // Coloca un mensaje de error intuitivo
            std::cout << "^ Error: ingreso invalido.\n";
        }
    }
}

bool verificar(std::string codigo) {
    int suma = 0;

    for (int i = 0; i < codigo.length() - 1; i++) {
        if (!isdigit(codigo[i])) return false;
        suma += codigo[i] - '0';
    }

    int digitoVerificador = codigo.back() - '0';

    return (suma % 7) == digitoVerificador;
}

int main(int argc, char* argv[]) {
    int intentos = 3;
    std::string codigo;
    bool bandera = false;

    if (argc == 2) {
        try {
            codigo = argv[1];
            if (codigo.length() != 5) throw std::invalid_argument("");
            std::cout << " < Codigo recibido como parametro.\n";
            bandera = true;
        } catch (...) {}
    }

    while (intentos > 0) {
        if (!bandera) codigo = ingresar("su codigo");

        std::cout << "  << Acceso ";
        if (verificar(codigo)) {
            std::cout << "concedido. Bienvenido.\n";
            break;
        } else {
            std::cout << "denegado.";
            intentos -= 1;
            bandera = false;
        }
    }
    if (intentos == 0) std::cout << " Se ha bloqueado el sistema.\n";
    std::cout << std::endl;

    return 0;
}
