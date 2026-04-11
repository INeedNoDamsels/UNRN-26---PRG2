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

    friend std::istream& operator>>(std::istream& is, Contacto& c);
    friend std::ostream& operator<<(std::ostream& os, const Contacto& c);
};

std::istream& operator>>(std::istream& is, Contacto& c) {
    int index = 0;
    size_t pos = 0;
    std::string linea;

    std::string campos[4] = {
        "", // [0] nombre
        "", // [1] apellido
        "", // [2] telefono
        "" //  [3] email
    };

    std::getline(is >> std::ws, linea);

    // separar por ';'
    while ((pos = linea.find(';')) != std::string::npos && index < 3) {
        campos[index++] = linea.substr(0, pos);
        linea.erase(0, pos + 1);
    }

    if (index < 4) campos[index++] = linea;

    if (campos[0].empty() && campos[1].empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    c.setNombreApellido(campos[0], campos[1]);
    c.setTelefono(campos[2]);
    c.setEmail(campos[3]);

    return is;
}


std::ostream& operator<<(std::ostream& os, const Contacto& c) {
    os << c.mostrarNombre() << " " << c.mostrarApellido()
       << "\n - Celular: " << c.mostrarTelefono()
       << "\n -  Correo: " << c.mostrarEmail();

    return os;
}

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

    bool agregarContacto(const Contacto& c) {
        if (this->cantidad >= MAX) return false;

        contactos[this->cantidad++] = c;

        return true;
    }

    const Contacto* obtenerContacto(int indice) const {
        return esIndiceValido(indice) ? &this->contactos[indice] : nullptr;
    }

    int mostrarCantidad() const { return this->cantidad; }

    bool editarContacto(int indice, const Contacto& c) {
        if (!esIndiceValido(indice)) return false;

        this->contactos[indice] = c;

        return true;
    }

    bool borrarContacto(int indice) {
        if (!esIndiceValido(indice)) return false;

        for (int i = indice; i < this->cantidad - 1; i++) this->contactos[i] = this->contactos[i + 1];
        this->cantidad--;

        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const AgendaDeContactos& agenda);
};

std::ostream& operator<<(std::ostream& os, const AgendaDeContactos& agenda) {
    int cantidad = agenda.mostrarCantidad();

    if (cantidad == 0) {
        os << "\nNo hay contactos para mostrar." << std::endl;

        return os;
    }

    for (int i = 0; i < cantidad; i++) {
        const Contacto* contacto = agenda.obtenerContacto(i);

        if (contacto) { // simula un apodo con iniciales variables
            char segundaInicial = ' ';
            std::string nombre = contacto->mostrarNombre();
            std::string apellido = contacto->mostrarApellido();

            if (!apellido.empty()) {
                segundaInicial = std::toupper(apellido[0]);
            } else if (nombre.length() > 1) {
                segundaInicial = nombre[1];
            } else if (!nombre.empty()) segundaInicial = nombre[0];

            os << "(" << (nombre.empty() ? '?' : nombre[0])
               << segundaInicial << ": "
               << i + 1 << ") "
               << *contacto << std::endl;
        }
    }

    os << "\nTotal de contactos: " << cantidad << std::endl;

    return os;
}

void menu() {
    std::cout << "\n\t Agenda de contactos"
              << "\n\t      <1> Nuevo\n\t<2> Editar <3> Borrar\n\t <4> Abrir mi agenda\n\t      <0> Salir" << std::endl;
}

void mostrarMensaje(bool exito, const std::string& mensajeExito, const std::string& mensajeError) {
    if (exito) {
        std::cout << "\n" << mensajeExito << std::endl;
    } else std::cout << "\n" << mensajeError << std::endl;
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
    int cantidad;
    bool continuar = true;
    Contacto miContacto;
    AgendaDeContactos agenda;

    while (continuar) {
        menu();
        cantidad = agenda.mostrarCantidad();

        int opcion = ingresarValor("\n > Seleccione operacion: ", 0, 4);

        switch (opcion) {
            case 0: {
                continuar = false;
                break;
            }

            // Agregar un nuevo contacto a la agenda, ahora utilizando operadores de entrada sobrecargados
            case 1: {
                std::cout << "  < Ingrese datos del nuevo contacto (';' para separar): ";

                if (!(std::cin >> miContacto)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "\nNombre y apellido no pueden estar vacios." << std::endl;
                } else mostrarMensaje(agenda.agregarContacto(miContacto), "Contacto agregado correctamente.", "Agenda llena.");
                break;
            }

            // Editar un contacto existente en la agenda, ahora utilizando operadores de entrada sobrecargados
            case 2: {
                if (cantidad == 0) {
                    std::cout << "\nNo hay contactos para editar." << std::endl;
                } else {
                    int id = ingresarValor(" > Ingrese el ID del contacto a editar: ", 1, cantidad) - 1;

                    std::cout << "  < Ingrese nuevos datos para el contacto [" << id + 1 << "]: ";
                    
                    if (!(std::cin >> miContacto)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        std::cout << "\nNombre y apellido no pueden estar vacios." << std::endl;
                    } else mostrarMensaje(agenda.editarContacto(id, miContacto), "Contacto editado correctamente.", "Contacto no encontrado.");
                }
                break;
            }

            // Borrar un contacto existente en la agenda
            case 3: {
                if (cantidad == 0) {
                    std::cout << "\nNo hay contactos para borrar." << std::endl;
                } else {
                    int id = ingresarValor(" > Ingrese el ID del contacto a borrar: ", 1, cantidad) - 1;

                    mostrarMensaje(agenda.borrarContacto(id), "Contacto borrado correctamente.", "Contacto no encontrado.");
                }
                break;
            }

            // Mostrar la lista de contactos en la agenda
            case 4: {
                std::cout << agenda;
                break;
            }

            default:
                break;
        }
    }

    return 0;
}
