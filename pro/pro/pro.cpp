#include <mysql.h> // para conectar a la base de datos y manipular 
#include <iostream>
#include <iomanip> // para usar setw
#include <string>
using namespace std;
// Códigos ANSI para colores
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
class BaseDeDatos {
public:
    BaseDeDatos(const string& host, const string& usuario, const string& clave, const string& nombreBD, unsigned int puerto) {
        conn = mysql_init(0);
        if (conn) {
            conn = mysql_real_connect(conn, host.c_str(), usuario.c_str(), clave.c_str(), nombreBD.c_str(), puerto, NULL, 0);
            // intenta conectarse a la base de datos utilizando mysql_real_connect.
            if (conn) {
                cout << GREEN << "Conectado a la Base de Datos" << RESET << endl;
            }
            else {
                cout << RED << "No fue posible conectarse a la Base de Datos: " << mysql_error(conn) << RESET << endl;
                // en caso en no conectar utiliza mysql_error(conn).
            }
        }
        else {
            cout << RED << "mysql_init() fallo" << RESET << endl;
        }
    }

    ~BaseDeDatos() {
        if (conn) {
            mysql_close(conn); //Cierra de forma segura la conexión a la base de datos utilizando mysql_close(conn)
        }
    }

    MYSQL* getConexion() const {  // Suponiendo una conexión exitosa, puede utilizar el método getConexion()
        return conn;
    }
private:
    MYSQL* conn; //Almacena el identificador de conexión obtenido de las funciones de la biblioteca MySQL.
};

class Pasajero {
public:
    Pasajero(const string& nombre, const string& apellido, const string& correo, const string& telefono)
        : nombre(nombre), apellido(apellido), correo(correo), telefono(telefono) {}

    void agregar(MYSQL* conn) {
        string query = "INSERT INTO passengers (nombre, apellido, correo, telefono) VALUES ('" + nombre + "', '" + apellido + "', '" + correo + "', '" + telefono + "')";
        if (mysql_query(conn, query.c_str())) {
            cout << RED << "Error al agregar pasajero: " << mysql_error(conn) << RESET << endl;
        }
        else {
            cout << GREEN << "Pasajero agregado!" << RESET << endl;
        }
    }

    static void listar(MYSQL* conn) {
        if (mysql_query(conn, "SELECT * FROM passengers")) {
            cout << RED << "Error al listar pasajeros: " << mysql_error(conn) << RESET << endl;
        }
        else {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row;

            // Imprimir encabezado de la tabla
            cout << "\n" << left << setw(10) << "ID" << setw(20) << "Nombre" << setw(20) << "Apellido" << setw(30) << "Correo" << setw(15) << "Telefono" << endl;
            cout << "-------------------------------------------------------------------------------" << endl;

            // Imprimir filas de datos
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0] << setw(20) << row[1] << setw(20) << row[2] << setw(30) << row[3] << setw(15) << row[4] << endl;
            }
            mysql_free_result(res);
            cout << "-------------------------------------------------------------------------------\n" << endl;
        }
    }

    static void actualizar(MYSQL* conn, int id, const string& nombre, const string& apellido, const string& correo, const string& telefono) {
        string query = "UPDATE passengers SET nombre='" + nombre + "', apellido='" + apellido + "', correo='" + correo + "', telefono='" + telefono + "' WHERE id=" + to_string(id);
        if (mysql_query(conn, query.c_str())) {
            cout << RED << "Error al actualizar pasajero: " << mysql_error(conn) << RESET << endl;
        }
        else {
            cout << GREEN << "Pasajero actualizado!" << RESET << endl;
        }
    }

    static void borrar(MYSQL* conn, int id) {
        string query = "DELETE FROM passengers WHERE id=" + to_string(id);
        if (mysql_query(conn, query.c_str())) {
            cout << RED << "Error al borrar pasajero: " << mysql_error(conn) << RESET << endl;
        }
        else {
            cout << GREEN << "Pasajero borrado!" << RESET << endl;
        }
    }
    static void buscar(MYSQL* conn, const string& nombre) {
        string query = "SELECT * FROM passengers WHERE nombre LIKE '%" + nombre + "%'";
        if (mysql_query(conn, query.c_str())) {
            cout << RED << "Error al buscar pasajero: " << mysql_error(conn) << RESET << endl;
        }
        else {
            MYSQL_RES* res = mysql_store_result(conn);
            if (mysql_num_rows(res) == 0) {
                cout << YELLOW << "No se encontraron datos relacionados." << RESET << endl;
            }
            else {
                MYSQL_ROW row;
                cout << "\n" << left << setw(10) << "ID" << setw(20) << "Nombre" << setw(20) << "Apellido" << setw(30) << "Correo" << setw(15) << "Telefono" << endl;
                cout << "-------------------------------------------------------------------------------" << endl;
                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(10) << row[0] << setw(20) << row[1] << setw(20) << row[2] << setw(30) << row[3] << setw(15) << row[4] << endl;
                }
            }
            mysql_free_result(res);
            cout << "-------------------------------------------------------------------------------\n" << endl;
        }
    }

private:
    string nombre;
    string apellido;
    string correo;
    string telefono;
};

class Vuelo {
public:
    Vuelo(const string& numero_vuelo, const string& origen, const string& destino, const string& fecha_hora_salida, const string& fecha_hora_llegada)
        : numero_vuelo(numero_vuelo), origen(origen), destino(destino), fecha_hora_salida(fecha_hora_salida), fecha_hora_llegada(fecha_hora_llegada) {}

    void agregar(MYSQL* conn) {
        string query = "INSERT INTO flights (numero_vuelo, origen, destino, fecha_hora_salida, fecha_hora_llegada) VALUES ('" + numero_vuelo + "', '" + origen + "', '" + destino + "', '" + fecha_hora_salida + "', '" + fecha_hora_llegada + "')";
        if (mysql_query(conn, query.c_str())) {
            cout << RED << "Error al agregar vuelo: " << mysql_error(conn) << RESET << endl;
        }
        else {
            cout << GREEN << "Vuelo agregado!" << RESET << endl;
        }
    }

    static void listar(MYSQL* conn) {
        if (mysql_query(conn, "SELECT * FROM flights")) {
            cout << RED << "Error al listar vuelos: " << mysql_error(conn) << RESET << endl;
        }
        else {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row;

            // Imprimir encabezado de la tabla
            cout << "\n" << left << setw(10) << "ID" << setw(20) << "Numero de Vuelo" << setw(20) << "Origen" << setw(20) << "Destino" << setw(25) << "Fecha y Hora de Salida" << setw(25) << "Fecha y Hora de Llegada" << endl;
            cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;

            // Imprimir filas de datos
            while ((row = mysql_fetch_row(res))) {
                cout << left << setw(10) << row[0] << setw(20) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(25) << row[4] << setw(25) << row[5] << endl;
            }
            mysql_free_result(res);
            cout << "----------------------------------------------------------------------------------------------------------------------------\n" << endl;
        }
    }

    static void actualizar(MYSQL* conn, int id, const string& numero_vuelo, const string& origen, const string& destino, const string& fecha_hora_salida, const string& fecha_hora_llegada) {
        string query = "UPDATE flights SET numero_vuelo='" + numero_vuelo + "', origen='" + origen + "', destino='" + destino + "', fecha_hora_salida='" + fecha_hora_salida + "', fecha_hora_llegada='" + fecha_hora_llegada + "' WHERE id=" + to_string(id);
        if (mysql_query(conn, query.c_str())) {
            cout << RED << "Error al actualizar vuelo: " << mysql_error(conn) << RESET << endl;
        }
        else {
            cout << GREEN << "Vuelo actualizado!" << RESET << endl;
        }
    }

    static void borrar(MYSQL* conn, int id) {
        string query = "DELETE FROM flights WHERE id=" + to_string(id);
        if (mysql_query(conn, query.c_str())) {
            cout << RED << "Error al borrar vuelo: " << mysql_error(conn) << RESET << endl;
        }
        else {
            cout << GREEN << "Vuelo borrado!" << RESET << endl;
        }
    }

    static void buscar(MYSQL* conn, const string& numero_vuelo) {
        string query = "SELECT * FROM flights WHERE numero_vuelo LIKE '%" + numero_vuelo + "%'";
        if (mysql_query(conn, query.c_str())) {
            cout << RED << "Error al buscar vuelo: " << mysql_error(conn) << RESET << endl;
        }
        else {
            MYSQL_RES* res = mysql_store_result(conn);
            if (mysql_num_rows(res) == 0) {
                cout << YELLOW << "No se encontraron datos relacionados." << RESET << endl;
            }
            else {
                MYSQL_ROW row;
                cout << "\n" << left << setw(10) << "ID" << setw(20) << "Numero de Vuelo" << setw(20) << "Origen" << setw(20) << "Destino" << setw(25) << "Fecha y Hora de Salida" << setw(25) << "Fecha y Hora de Llegada" << endl;
                cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(10) << row[0] << setw(20) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(25) << row[4] << setw(25) << row[5] << endl;
                }
            }
            mysql_free_result(res);
            cout << "----------------------------------------------------------------------------------------------------------------------------\n" << endl;
        }
    }

private:
    string numero_vuelo;
    string origen;
    string destino;
    string fecha_hora_salida;
    string fecha_hora_llegada;
};

void mostrarSubMenuPasajeros(MYSQL* conn) { // creacion del sub menu pasajeros 
    int opcion = 0;
    while (opcion != 6) {
        cout << BLUE << "\n--- Menu Pasajeros ---" << RESET << endl;
        cout << YELLOW << "1. Agregar Pasajero" << RESET << endl;
        cout << YELLOW << "2. Listar Pasajero" << RESET << endl;
        cout << YELLOW << "3. Actualizar Pasajero" << RESET << endl;
        cout << YELLOW << "4. Borrar Pasajero" << RESET << endl;
        cout << YELLOW << "5. Buscar Pasajero" << RESET << endl;
        cout << YELLOW << "6. Volver al menu principal" << RESET << endl;
        cout << GREEN << "Seleccione una opcion: " << RESET;
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
        case 1: {
            string nombre, apellido, correo, telefono;
            cout << "Ingrese nombre: ";
            getline(cin, nombre);
            cout << "Ingrese apellido: ";
            getline(cin, apellido);
            cout << "Ingrese correo: ";
            getline(cin, correo);
            cout << "Ingrese telefono: ";
            getline(cin, telefono);
            Pasajero pasajero(nombre, apellido, correo, telefono);
            pasajero.agregar(conn);
            break;
        }
        case 2:
            Pasajero::listar(conn);
            break;
        case 3: {
            int id;
            string nombre, apellido, correo, telefono;
            cout << "Ingrese ID del pasajero a actualizar: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese nuevo nombre: ";
            getline(cin, nombre);
            cout << "Ingrese nuevo apellido: ";
            getline(cin, apellido);
            cout << "Ingrese nuevo correo: ";
            getline(cin, correo);
            cout << "Ingrese nuevo teléfono: ";
            getline(cin, telefono);
            Pasajero::actualizar(conn, id, nombre, apellido, correo, telefono);
            break;
        }
        case 4: {
            int id;
            cout << "Ingrese ID del pasajero a borrar: ";
            cin >> id;
            cin.ignore();
            Pasajero::borrar(conn, id);
            break;
        }
        case 5: {
            string nombre;
            cout << "Ingrese nombre del pasajero a buscar: ";
            getline(cin, nombre);
            Pasajero::buscar(conn, nombre);
            break;
        }
        case 6:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << RED << "Opción invalida, por favor intente nuevamente." << RESET << endl;
        }
    }
}

void mostrarSubMenuVuelos(MYSQL* conn) { //Crear el submenu vuelos
    int opcion = 0;
    while (opcion != 6) {
        cout << BLUE << "\n--- Menu Vuelos ---" << RESET << endl;
        cout << YELLOW << "1. Agregar vuelo" << RESET << endl;
        cout << YELLOW << "2. Listar vuelo" << RESET << endl;
        cout << YELLOW << "3. Actualizar vuelo" << RESET << endl;
        cout << YELLOW << "4. Borrar vuelo" << RESET << endl;
        cout << YELLOW << "5. Buscar vuelo" << RESET << endl;
        cout << YELLOW << "6. Volver al menu principal" << RESET << endl;
        cout << GREEN << "Seleccione una opcion: " << RESET;
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
        case 1: {
            string numero_vuelo, origen, destino, fecha_hora_salida, fecha_hora_llegada;
            cout << "Ingrese numero de vuelo: ";
            getline(cin, numero_vuelo);
            cout << "Ingrese origen: ";
            getline(cin, origen);
            cout << "Ingrese destino: ";
            getline(cin, destino);
            cout << "Ingrese fecha y hora de salida (YYYY-MM-DD HH:MM:SS): ";
            getline(cin, fecha_hora_salida);
            cout << "Ingrese fecha y hora de llegada (YYYY-MM-DD HH:MM:SS): ";
            getline(cin, fecha_hora_llegada);
            Vuelo vuelo(numero_vuelo, origen, destino, fecha_hora_salida, fecha_hora_llegada);
            vuelo.agregar(conn);
            break;
        }
        case 2:
            Vuelo::listar(conn);
            break;
        case 3: {
            int id;
            string numero_vuelo, origen, destino, fecha_hora_salida, fecha_hora_llegada;
            cout << "Ingrese ID del vuelo a actualizar: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese nuevo numero de vuelo: ";
            getline(cin, numero_vuelo);
            cout << "Ingrese nuevo origen: ";
            getline(cin, origen);
            cout << "Ingrese nuevo destino: ";
            getline(cin, destino);
            cout << "Ingrese nueva fecha y hora de salida (YYYY-MM-DD HH:MM:SS): ";
            getline(cin, fecha_hora_salida);
            cout << "Ingrese nueva fecha y hora de llegada (YYYY-MM-DD HH:MM:SS): ";
            getline(cin, fecha_hora_llegada);
            Vuelo::actualizar(conn, id, numero_vuelo, origen, destino, fecha_hora_salida, fecha_hora_llegada);
            break;
        }
        case 4: {
            int id;
            cout << "Ingrese ID del vuelo a borrar: ";
            cin >> id;
            cin.ignore();
            Vuelo::borrar(conn, id);
            break;
        }
        case 5: {
            string numero_vuelo;
            cout << "Ingrese número de vuelo a buscar: ";
            getline(cin, numero_vuelo);
            Vuelo::buscar(conn, numero_vuelo);
            break;
        }
        case 6:
            cout << "Volviendo al menú principal..." << endl;
            break;
        default:
            cout << RED << "Opcion inválida, por favor intente nuevamente." << RESET << endl;
        }
    }
}

void mostrarMenuPrincipal() {
    cout << RED << "\n--- AEROLINEAS QUETZAL ---" << RESET << endl;
    cout << BLUE << "1. Menu Pasajeros" << RESET << endl;
    cout << BLUE << "2. Menu Vuelo" << RESET << endl;
    cout << BLUE << "3. Salir" << RESET << endl;
    cout << GREEN << "Seleccione una opcion:" << RESET << endl;
}
int main() {
    BaseDeDatos bd("localhost", "root", "123456", "pase_de_abordaje", 3306); // para tener acceso a la base de datos, imgresar contraseña
    MYSQL* conn = bd.getConexion();

    if (conn) {
        int opcion = 0;
        while (opcion != 3) {
            mostrarMenuPrincipal();
            cin >> opcion;
            cin.ignore(); // Limpiar el buffer

            switch (opcion) {
            case 1:
                mostrarSubMenuPasajeros(conn);
                break;
            case 2:
                mostrarSubMenuVuelos(conn);
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << RED << "Opción invalida, por favor intente nuevamente." << RESET << endl;
            }
        }
    }

    return 0;
}



