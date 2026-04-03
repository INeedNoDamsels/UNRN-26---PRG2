// 2. Clases con Arreglos Estáticos

#include <iostream>
#include <string>

/**
 * Punto 2, inciso 1.
 * 
 * Clase que contiene los datos de un contacto y permite editarlos.
 */
class Contacto {
private:
    std::string nombre;
    std::string apellido;
    std::string telefono;
    std::string email;

public:
    Contacto() : nombre(""), apellido(""), telefono(""), email("") {}
    Contacto(const std::string& n, const std::string& a, const std::string& t = "", const std::string& e = "") {
        if (n.empty() && a.empty()) {
            this->nombre = "Nuevo";
            this->apellido = "contacto";
        } else {
            this->nombre = n;
            this->apellido = a;
        }

        this->telefono = t;
        this->email = e;
    }

    bool setNombreApellido(const std::string& n, const std::string& a) {
        if (n.empty() && a.empty()) { return false; }

        this->nombre = n;
        this->apellido = a;

        return true;
    }
    void setTelefono(const std::string& t) { this->telefono = t; }
    void setEmail(const std::string& e) { this->email = e; }

    void mostrar() const {
        bool tieneApellido  = !apellido.empty();
        char segundaInicial = '?';

        if (tieneApellido) {
            segundaInicial = apellido.at(0);
        } else if (nombre.length() > 1) {
            segundaInicial = nombre.at(1);
        } else { segundaInicial = nombre.at(0);}

        std::cout << "\n(" << nombre.at(0) << segundaInicial << ") "
                  << "Nombre: " << nombre << (tieneApellido ? " " + apellido : "")
                  << "\n - Celular: " << telefono << "\n - Correo: " << email << std::endl;
    }
};

/**
 * Punto 2, inciso 3.
 * 
 * Clase que implementa las operaciones de agregar, editar, eliminar y acceder a los contactos.
 */
class AgendaDeContactos {
};

void menu() {
    std::cout << "\n\t Agenda de contactos"
              << "\n\t     <1> Nuevo\n\t<2> Editar <3> Borrar\n\t <4> Abrir mi agenda\n\t      <0> Salir" << std::endl;
}

int ingresar(const std::string& mensaje) {
    int valor;

    while (true) {
        std::string input;
        std::cout << mensaje; std::cin >> input;

        try {
            valor = std::stoi(input);
            if (valor < 0) throw std::invalid_argument("");
            return valor;
        } catch (...) {
            for (int i = 0; i < mensaje.length() ; i++) std::cout << " ";
            std::cout << "^ Aviso: opcion invalida." << std::endl;
        }
    }
}

int main() {
    bool continuar = true;

    while (continuar) {
        menu();

        switch (ingresar("\n > Seleccione operacion: ")) {
        case 0:
            continuar = false;
            break;
        case 1:
            std::cout << "\n - Nuevo contacto" << std::endl;
            break;
        case 2:
            std::cout << "\n - Editar contacto" << std::endl;
            break;
        case 3:
            std::cout << "\n - Borrar contacto" << std::endl;
            break;
        case 4:
            std::cout << "\n - Mi agenda" << std::endl;
            break;
        default:
            break;
        }
    }

    return 0;
}
