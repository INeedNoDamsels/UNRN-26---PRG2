// 2. Clases con Arreglos Estáticos

#include <iostream>
#include <string>
#include <limits>

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

    void mostrarContacto() const {
        char segundaInicial;

        if (!apellido.empty()) {
            segundaInicial = std::toupper(apellido[0]);
        } else if (nombre.length() > 1) {
            segundaInicial = nombre[1];
        } else segundaInicial = this->nombre[0];

        std::cout << "(" << this->nombre[0] << segundaInicial << ") "
                  << this->nombre << (this->apellido.empty() ? "" : " " + this->apellido)
                  << "\n - Celular: " << (this->telefono.empty() ? "*vacio*" : this->telefono)
                  << "\n -  Correo: " << (this->email.empty() ? "*vacio*" : this->email) << std::endl;
    }
};

/**
 * Punto 2, inciso 3.
 * 
 * Clase que implementa las operaciones de agregar, editar, eliminar y acceder a los contactos.
 */
class AgendaDeContactos {
private:
    static const int MAX = 10;
    Contacto contactos[MAX];
    int cantidad;

public:
    AgendaDeContactos() : cantidad(0) {}

    bool agregarContacto(const std::string& nombre, const std::string& apellido, const std::string& telefono = "", const std::string& email = "") {
        if (this->cantidad >= MAX) return false;

        Contacto c(nombre, apellido, telefono, email);
        contactos[cantidad] = c;
        cantidad += 1;

        return true;
    }

    bool mostrarAgenda() const {
        if (this->cantidad == 0) return false;

        for (int i = 0; i < this->cantidad; i++) contactos[i].mostrarContacto();

        return true;
    }

    int mostrarCantidad() const { return this->cantidad;}
};

void menu() {
    std::cout << "\n\t Agenda de contactos"
              << "\n\t      <1> Nuevo\n\t<2> Editar <3> Borrar\n\t <4> Abrir mi agenda\n\t      <0> Salir" << std::endl;
}

std::string ingresarTexto(const std::string& mensaje) {
    std::string input;

    std::cout << mensaje; std::getline(std::cin, input);

    return input;
}

int ingresarValor(const std::string& mensaje) {
    int valor;

    while (true) {
        std::string input;
        std::cout << mensaje; std::cin >> input;

        try {
            valor = std::stoi(input);
            if (valor < 0 || valor > 4) throw std::invalid_argument("");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            return valor;
        } catch (...) {
            for (int i = 1; i < mensaje.length() ; i++) std::cout << " ";
            std::cout << "^ Aviso: opcion invalida." << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main() {
    std::string nombre, apellido, telefono, email;
    AgendaDeContactos agenda;
    bool continuar = true;

    while (continuar) {
        menu();

        switch (ingresarValor("\n > Seleccione operacion: ")) {
        case 0:
            continuar = false;
            break;
        case 1:
            nombre   = ingresarTexto("  < Ingrese nombre: ");
            apellido = ingresarTexto("  < Ingrese apellido: ");
            telefono = ingresarTexto("  < Ingrese telefono: ");
            email    = ingresarTexto("  < Ingrese email: ");

            if (agenda.agregarContacto(nombre, apellido, telefono, email)) {
                std::cout << "\nContacto agregado correctamente." << std::endl;
            } else std::cout << "\nAgenda llena." << std::endl;
            break;
        case 2:
            std::cout << "\n - Editar contacto" << std::endl;
            break;
        case 3:
            std::cout << "\n - Borrar contacto" << std::endl;
            break;
        case 4:
            if (!agenda.mostrarAgenda()) {
                std::cout << "\nNo hay contactos para mostrar." << std::endl;
            } else std::cout << "\nTotal de contactos: " << agenda.mostrarCantidad() << std::endl;
            break;
        default:
            break;
        }
    }

    return 0;
}
