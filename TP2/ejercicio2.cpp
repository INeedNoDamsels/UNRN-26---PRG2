// 2. Clases con Arreglos Estáticos

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

// ===== CONTACTO =========================================
class Contacto {
private:
    std::string nombre;
    std::string apellido;
    std::string telefono;
    std::string email;

    bool esNombreApellidoValido(const std::string& n, const std::string& a) const {
        return !(n.empty() && a.empty());
    }

    bool esTelefonoValido(const std::string& t) const {
        if (t.empty()) return true;

        int i = 0;

        if (t[0] == '+') i = 1;

        for (; i < (int)t.size(); i++) if (!std::isdigit(t[i]) && t[i] != ' ') return false;

        return true;
    }

public:
    Contacto() : nombre(""), apellido(""), telefono(""), email("") {}

    Contacto(const std::string& n, const std::string& a, const std::string& t = "", const std::string& e = "") {
        if (!esNombreApellidoValido(n, a)) throw std::invalid_argument("Nombre y apellido invalidos");
        if (!esTelefonoValido(t)) throw std::invalid_argument("Telefono invalido");

        nombre   = n;
        apellido = a;
        telefono = t;
        email    = e;
    }

    bool setNombreApellido(const std::string& n, const std::string& a) {
        if (!esNombreApellidoValido(n, a)) return false;

        nombre   = n;
        apellido = a;

        return true;
    }

    bool setTelefono(const std::string& t) {
        if (!esTelefonoValido(t)) return false;

        telefono = t;

        return true;
    }

    void setEmail(const std::string& e) { email = e; }

    std::string mostrarNombre()   const { return nombre; }
    std::string mostrarApellido() const { return apellido; }
    std::string mostrarTelefono() const { return telefono; }
    std::string mostrarEmail()    const { return email; }

    bool mismoContacto(const Contacto& otro) const {
        return nombre == otro.nombre && apellido == otro.apellido;
    }

    friend std::ostream& operator<<(std::ostream& os, const Contacto& c);
    friend std::istream& operator>>(std::istream& is, Contacto& c);
};

std::ostream& operator<<(std::ostream& os, const Contacto& c) {
    os << c.nombre << ";" << c.apellido << ";" << c.telefono << ";" << c.email;

    return os;
}

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

// ===== AGENDA ===========================================
class AgendaDeContactos {
private:
    static const int MAX = 99;
    Contacto contactos[MAX];
    int cantidad;

    bool esIndiceValido(int i) const { return i >= 0 && i < cantidad; }

    int buscar(const Contacto& c) const {
        for (int i = 0; i < cantidad; i++) {
            if (contactos[i].mismoContacto(c)) return i;
        }

        return -1;
    }

    static bool comparar(const Contacto& a, const Contacto& b) {
        if (a.mostrarApellido() == b.mostrarApellido()) return a.mostrarNombre() < b.mostrarNombre();

        return a.mostrarApellido() < b.mostrarApellido();
    }

public:
    AgendaDeContactos() : cantidad(0) {}

    bool actualizar(const Contacto& c) {
        int pos = buscar(c);

        if (pos != -1) {
            contactos[pos] = c;
            return true;
        }

        if (cantidad >= MAX) return false;

        contactos[cantidad++] = c;

        return true;
    }

    bool editarContacto(int indice, const Contacto& c) {
        if (!esIndiceValido(indice)) return false;

        contactos[indice] = c;

        return true;
    }

    bool borrarContacto(int indice) {
        if (!esIndiceValido(indice)) return false;

        for (int i = indice; i < cantidad - 1; i++) contactos[i] = contactos[i + 1];

        cantidad--;

        return true;
    }

    const Contacto* obtenerContacto(int indice) const {
        return esIndiceValido(indice) ? &contactos[indice] : nullptr;
    }

    int mostrarCantidad() const { return cantidad; }

    friend std::ostream& operator<<(std::ostream& os, AgendaDeContactos a);
    friend std::istream& operator>>(std::istream& is, AgendaDeContactos& a);
    friend void mostrarAgendaVisual(const AgendaDeContactos& a);
};

std::ostream& operator<<(std::ostream& os, AgendaDeContactos a) {
    std::sort(a.contactos, a.contactos + a.cantidad, AgendaDeContactos::comparar);

    for (int i = 0; i < a.cantidad; i++) os << a.contactos[i] << "\n";

    return os;
}

std::istream& operator>>(std::istream& is, AgendaDeContactos& a) {
    Contacto c;

    while (is >> c) {
        a.actualizar(c);
    }

    return is;
}

// ===== UTILS ============================================
void menu() {
    std::cout << "\n\t Agenda de contactos"
              << "\n\t      <1> Nuevo\n\t<2> Editar <3> Borrar\n\t <4> Abrir mi agenda\n\t      <0> Salir" << std::endl;
}

void mostrarAgendaVisual(const AgendaDeContactos& a) {

    for (int i = 0; i < a.mostrarCantidad(); i++) {
        const Contacto* contacto = a.obtenerContacto(i);

        char segundaInicial = ' ';
        std::string nombre   = contacto->mostrarNombre();
        std::string apellido = contacto->mostrarApellido();
        std::string telefono = contacto->mostrarTelefono();
        std::string email    = contacto->mostrarEmail();

        if (!apellido.empty()) {
            segundaInicial = std::toupper(static_cast<unsigned char>(apellido[0]));
        } else if (nombre.length() > 1) {
            segundaInicial = nombre[1];
        } else if (!nombre.empty()) segundaInicial = nombre[0];

        std::cout << "\n(" << (nombre.empty() ? '?' : nombre[0])
                  << segundaInicial << ": "
                  << i + 1 << ") "
                  << nombre << " " << apellido
                  << "\n - Celular: " << telefono
                  << "\n -  Correo: " << email << std::endl;
    }
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

// ===== PROGRAMA PPAL ====================================
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
                } else mostrarMensaje(agenda.actualizar(miContacto), "Contacto agregado correctamente.", "Agenda llena.");
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
                mostrarAgendaVisual(agenda);
                break;
            }

            default:
                break;
        }
    }

    return 0;
}
