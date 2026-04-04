#include <iostream>
#include <string>
#include <limits>
#include <cctype>

/**
 * Clase que contiene los datos de un contacto y permite editarlos.
 */
class Contacto {
private:
    std::string nombre;
    std::string apellido;
    std::string telefono;
    std::string email;

    bool esNombreApellidoValido(const std::string& n, const std::string& a) const {
        return !(n.empty() && a.empty());
    }

public:
    Contacto() : nombre(""), apellido(""), telefono(""), email("") {}
    Contacto(const std::string& n, const std::string& a, const std::string& t = "", const std::string& e = "") {
        if (esNombreApellidoValido(n, a)) {
            this->nombre = n;
            this->apellido = a;
        } else {
            this->nombre = "Nuevo";
            this->apellido = "contacto";
        }

        this->telefono = t;
        this->email = e;
    }

    bool setNombreApellido(const std::string& n, const std::string& a) {
        if (!esNombreApellidoValido(n, a)) return false;

        this->nombre = n;
        this->apellido = a;

        return true;
    }
    void setTelefono(const std::string& t) { this->telefono = t; }
    void setEmail(const std::string& e) { this->email = e; }

    std::string mostrarNombre() const { return this->nombre; }

    std::string mostrarApellido() const { return this-> apellido; }

    std::string mostrarTelefono() const { return this->telefono.empty() ? "*vacio*" : this->telefono; }

    std::string mostrarEmail() const { return this->email.empty() ? "*vacio*" : this->email; }

    std::string obtenerInfo() const {
        return this->nombre + " " + this->apellido + "\n - Celular: " + this->mostrarTelefono() + "\n -  Correo: " + this-> mostrarEmail();
    }
};

/**
 * Clase que implementa las operaciones de agregar, editar, eliminar y acceder a los contactos.
 */
class AgendaDeContactos {
private:
    int cantidad;
    static const int MAX = 9;
    Contacto contactos[MAX];

    bool esIndiceValido(int indice) const { return indice >= 0 && indice < this->cantidad; }

public:
    AgendaDeContactos() : cantidad(0) {}

    bool agregarContacto(const std::string& nombre, const std::string& apellido, const std::string& telefono = "", const std::string& email = "") {
        if (this->cantidad >= MAX) return false;

        contactos[this->cantidad++] = Contacto(nombre, apellido, telefono, email);

        return true;
    }

    const Contacto* obtenerContacto(int indice) const {
        return esIndiceValido(indice) ? &this->contactos[indice] : nullptr;
    }

    int mostrarCantidad() const { return this->cantidad; }

    bool editarContacto(int indice, const std::string& nombre, const std::string& apellido, const std::string& telefono = "", const std::string& email = "") {
        if (!esIndiceValido(indice)) return false;

        this->contactos[indice].setTelefono(telefono);
        this->contactos[indice].setEmail(email);

        return this->contactos[indice].setNombreApellido(nombre, apellido);
    }

    bool borrarContacto(int indice) {
        if (!esIndiceValido(indice)) return false;

        for (int i = indice; i < this->cantidad - 1; i++) this->contactos[i] = this->contactos[i + 1];
        this->cantidad--;

        return true;
    }
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

int ingresarValor(const std::string& mensaje, int min = 0, int max = 4) {
    int valor;

    while (true) {
        std::string input;

        std::cout << mensaje; std::cin >> input;
        try {
            valor = std::stoi(input);

            if (valor < min || valor > max) throw std::invalid_argument("");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            return valor;
        } catch (...) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for (int i = 0; i < mensaje.length() ; i++) std::cout << " ";
            std::cout << "^ Aviso: opcion invalida." << std::endl;
        }
    }
}

int main() {
    bool continuar = true;
    AgendaDeContactos agenda;

    while (continuar) {
        menu();

        int opcion = ingresarValor("\n > Seleccione operacion: ", 0, 4);

        switch (opcion) {
        case 0:
            continuar = false;
            break;

        // Agregar un nuevo contacto a la agenda
        case 1: {
            std::string n = ingresarTexto("  < Ingrese nombre: ");
            std::string a = ingresarTexto("  < Ingrese apellido: ");
            std::string t = ingresarTexto("  < Ingrese telefono: ");
            std::string e = ingresarTexto("  < Ingrese email: ");

            if (agenda.agregarContacto(n, a, t, e)) {
                std::cout << "\nContacto agregado correctamente." << std::endl;
            } else std::cout << "\nAgenda llena." << std::endl;
            break;
        }

        // Editar un contacto existente en la agenda
        case 2: {
            if (agenda.mostrarCantidad() == 0) {
                std::cout << "\nNo hay contactos para editar." << std::endl;
            } else {
                int id = ingresarValor(" > Ingrese el ID del contacto a editar: ", 1, agenda.mostrarCantidad()) - 1;
                std::string n = ingresarTexto("  < Ingrese nombre: ");
                std::string a = ingresarTexto("  < Ingrese apellido: ");
                std::string t = ingresarTexto("  < Ingrese telefono: ");
                std::string e = ingresarTexto("  < Ingrese email: ");

                if (agenda.editarContacto(id, n, a, t, e)) {
                    std::cout << "\nContacto editado correctamente." << std::endl;
                } else std::cout << "\nContacto no encontrado." << std::endl;
            }
            break;
        }

        // Borrar un contacto existente en la agenda
        case 3: {
            if (agenda.mostrarCantidad() == 0) {
                std::cout << "\nNo hay contactos para borrar." << std::endl;
            } else {
                int id = ingresarValor(" > Ingrese el ID del contacto a borrar: ", 1, agenda.mostrarCantidad()) - 1;

                if (agenda.borrarContacto(id)) {
                    std::cout << "\nContacto borrado correctamente." << std::endl;
                } else std::cout << "\nContacto no encontrado." << std::endl;
            }
            break;
        }

        // Mostrar la lista de contactos en la agenda
        case 4: {
            if (agenda.mostrarCantidad() == 0) {
                std::cout << "\nNo hay contactos para mostrar." << std::endl;
            } else {
                for (int i = 0; i < agenda.mostrarCantidad(); i++) {
                    const Contacto* miContacto = agenda.obtenerContacto(i);

                    if (miContacto) {
                        char segundaInicial = ' ';
                        std::string nombre = miContacto->mostrarNombre();
                        std::string apellido = miContacto->mostrarApellido();

                        if (!apellido.empty()) segundaInicial = std::toupper(apellido[0]);
                        else if (nombre.length() > 1) segundaInicial = nombre[1];
                        else if (!nombre.empty()) segundaInicial = nombre[0];

                        std::cout << "(" << (nombre.empty() ? '?' : nombre[0]) << segundaInicial << ": "
                                << i + 1 << ") " << miContacto->obtenerInfo() << std::endl;
                    }
                }
                std::cout << "\nTotal de contactos: " << agenda.mostrarCantidad() << std::endl;
            }
        break;
        }

        default:
            break;
        }
    }

    return 0;
}
