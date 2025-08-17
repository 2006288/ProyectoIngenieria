#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <chrono>
#include <iomanip>
#include <set>
using namespace std;

// Estructuras para almacenar los datos
struct Empleado {
    int id;
    string nombres;
    string apellidos;
    string direccion;
    string telefono;
    string correo;
};

struct RegistroHoras {
    int id;
    bool esSalida; // false para entrada, true para salida
    chrono::system_clock::time_point timestamp;
};

// Estructura para el reporte final
struct ReporteEmpleado {
    int id;
    string nombres;
    string apellidos;
    int faltas = 0;
    double totalHoras = 0.0;
};

// Prototipos de funciones
void cargarDatos(vector<Empleado>& empleados, vector<RegistroHoras>& registros);
void registrarDatosPersonales(vector<Empleado>& empleados);
void mostrarHorasPorEmpleado(const vector<Empleado>& empleados, const vector<RegistroHoras>& registros);
void imprimirReportePuntualidad(const vector<Empleado>& empleados, const vector<RegistroHoras>& registros);
void mostrarMenu();
string reemplazarEspacios(string texto);
string restaurarEspacios(string texto);

// Función para convertir partes de fecha/hora a time_point
chrono::system_clock::time_point make_timestamp(int anio, int mes, int dia, int hora, int min) {
    tm tm = {};
    tm.tm_year = anio - 1900;
    tm.tm_mon = mes - 1;
    tm.tm_mday = dia;
    tm.tm_hour = hora;
    tm.tm_min = min;
    return chrono::system_clock::from_time_t(mktime(&tm));
}

int main() {
    mostrarMenu();
    return 0;
}

void mostrarMenu() {
    vector<Empleado> empleados;
    vector<RegistroHoras> registros;
    cargarDatos(empleados, registros);

    int opcion;
    do {
        cout << "\n===============================" << endl;
        cout << "SISTEMA CONTROL DE EMPLEADOS" << endl;
        cout << "===============================" << endl;
        cout << "1.- Registrar nuevo empleado" << endl;
        cout << "2.- Mostrar registros de horas" << endl;
        cout << "3.- Imprimir reporte de Mejores Empleados" << endl;
        cout << "0.- Salir" << endl;
        cout << "===============================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarDatosPersonales(empleados);
                empleados.clear();
                registros.clear();
                cargarDatos(empleados, registros);
                break;
            case 2:
                mostrarHorasPorEmpleado(empleados, registros);
                break;
            case 3:
                imprimirReportePuntualidad(empleados, registros);
                break;
            case 0:
                cout << "Saliendo del sistema." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 0);
}

string reemplazarEspacios(string texto) {
    replace(texto.begin(), texto.end(), ' ', '_');
    return texto;
}

string restaurarEspacios(string texto) {
    replace(texto.begin(), texto.end(), '_', ' ');
    return texto;
}

void cargarDatos(vector<Empleado>& empleados, vector<RegistroHoras>& registros) {
    ifstream archivoEmpleados("empleados.txt");
    string linea;
    if (archivoEmpleados.is_open()) {
        while (getline(archivoEmpleados, linea)) {
            stringstream ss(linea);
            Empleado emp;
            ss >> emp.id >> emp.nombres >> emp.apellidos >> emp.direccion >> emp.telefono >> emp.correo;
            empleados.push_back(emp);
        }
        archivoEmpleados.close();
    }

    ifstream archivoHoras("horas.txt");
    if (archivoHoras.is_open()) {
        while (getline(archivoHoras, linea)) {
            stringstream ss(linea);
            RegistroHoras reg;
            int estado, hora, min, dia, mes, anio;
            char delim;
            ss >> reg.id >> estado >> hora >> delim >> min >> dia >> delim >> mes >> delim >> anio;
            reg.esSalida = (estado == 1);
            reg.timestamp = make_timestamp(anio, mes, dia, hora, min);
            registros.push_back(reg);
        }
        archivoHoras.close();
    }
}

void solicitarDatos(Empleado& empleado) {
    cin.ignore();
    cout << "Ingrese los dos Nombres: ";
    getline(cin, empleado.nombres);
    cout << "Ingrese los dos Apellidos: ";
    getline(cin, empleado.apellidos);
    cout << "Ingrese la direccion: ";
    getline(cin, empleado.direccion);
    cout << "Ingrese el telefono: ";
    getline(cin, empleado.telefono);
    cout << "Ingrese el correo: ";
    getline(cin, empleado.correo);
}

void registrarDatosPersonales(vector<Empleado>& empleados) {
    Empleado nuevoEmpleado;
    solicitarDatos(nuevoEmpleado);
    nuevoEmpleado.id = empleados.empty() ? 1 : empleados.back().id + 1;

    ofstream archivo("empleados.txt", ios::app);
    if (archivo.is_open()) {
        archivo << nuevoEmpleado.id << " "
                << reemplazarEspacios(nuevoEmpleado.nombres) << " "
                << reemplazarEspacios(nuevoEmpleado.apellidos) << " "
                << reemplazarEspacios(nuevoEmpleado.direccion) << " "
                << nuevoEmpleado.telefono << " "
                << nuevoEmpleado.correo << endl;
        cout << "Empleado registrado correctamente con ID: " << nuevoEmpleado.id << endl;
        archivo.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo empleados.txt para escribir." << endl;
    }
}

void mostrarHorasPorEmpleado(const vector<Empleado>& empleados, const vector<RegistroHoras>& registros) {
    for (const auto& emp : empleados) {
        cout << "\n------------------------------------" << endl;
        cout << "Empleado: " << restaurarEspacios(emp.nombres) << " " << restaurarEspacios(emp.apellidos) << endl;
        cout << "------------------------------------" << endl;

        for (const auto& reg : registros) {
            if (reg.id == emp.id) {
                time_t tiempo = chrono::system_clock::to_time_t(reg.timestamp);
                tm* tm = localtime(&tiempo);
                cout << "Fecha: " << put_time(tm, "%d/%m/%Y") << " | "
                          << "Hora: " << put_time(tm, "%H:%M") << " | "
                          << "Estado: " << (reg.esSalida ? "Salida" : "Entrada") << endl;
            }
        }
    }
}

void imprimirReportePuntualidad(const vector<Empleado>& empleados, const vector<RegistroHoras>& registros) {
    map<int, ReporteEmpleado> datosReporte;

    // Inicializar datos del reporte con la información del empleado
    for (const auto& emp : empleados) {
        datosReporte[emp.id].id = emp.id;
        datosReporte[emp.id].nombres = emp.nombres;
        datosReporte[emp.id].apellidos = emp.apellidos;
    }

    // Calcular faltas y horas trabajadas
    for (const auto& emp : empleados) {
        map<int, chrono::system_clock::time_point> primeraEntradaPorDia;
        vector<RegistroHoras> registrosEmpleado;

        for (const auto& reg : registros) {
            if (reg.id == emp.id) {
                registrosEmpleado.push_back(reg);
                if (!reg.esSalida) { // Si es una entrada
                    time_t tiempo = chrono::system_clock::to_time_t(reg.timestamp);
                    tm* tm_local = localtime(&tiempo);
                    int diaDelAnio = tm_local->tm_yday;

                    if (primeraEntradaPorDia.find(diaDelAnio) == primeraEntradaPorDia.end() || reg.timestamp < primeraEntradaPorDia[diaDelAnio]) {
                        primeraEntradaPorDia[diaDelAnio] = reg.timestamp;
                    }
                }
            }
        }

        // Contar faltas
        for (const auto& par : primeraEntradaPorDia) {
            time_t tiempo = chrono::system_clock::to_time_t(par.second);
            tm* tm_local = localtime(&tiempo);
            if (tm_local->tm_hour > 7 || (tm_local->tm_hour == 7 && tm_local->tm_min > 30)) {
                datosReporte[emp.id].faltas++;
            }
        }

        // Calcular horas trabajadas
        sort(registrosEmpleado.begin(), registrosEmpleado.end(), [](const RegistroHoras& a, const RegistroHoras& b) {
            return a.timestamp < b.timestamp;
        });

        for (size_t i = 0; i < registrosEmpleado.size(); ++i) {
            if (!registrosEmpleado[i].esSalida) { // Es una entrada
                // Buscar la siguiente salida
                for (size_t j = i + 1; j < registrosEmpleado.size(); ++j) {
                    if (registrosEmpleado[j].esSalida) {
                        auto diff = registrosEmpleado[j].timestamp - registrosEmpleado[i].timestamp;
                        datosReporte[emp.id].totalHoras += chrono::duration<double, ratio<3600>>(diff).count();
                        i = j; // Avanzar el índice principal para no re-contar
                        break;
                    }
                }
            }
        }
    }

    // Convertir el mapa a un vector para ordenarlo
    vector<ReporteEmpleado> empleadosOrdenados;
    for (const auto& par : datosReporte) {
        empleadosOrdenados.push_back(par.second);
    }

    // Ordenar segun el criterio: menos faltas, luego más horas
    sort(empleadosOrdenados.begin(), empleadosOrdenados.end(),
              [](const ReporteEmpleado& a, const ReporteEmpleado& b) {
                  if (a.faltas != b.faltas) {
                      return a.faltas < b.faltas; // Menos faltas es mejor
                  }
                  return a.totalHoras > b.totalHoras; // Más horas es mejor
              });

    // Imprimir el reporte
    cout << "\n--- Reporte de Mejores Empleados ---" << endl;
    cout << left << setw(5) << "ID" << setw(40) << "Empleado" << setw(40) << "Direccion" << setw(20)<< "Faltas" << setw(15) << "Horas Trab." << endl;
    cout << "---------------------------------------------------------------------" << endl;
    for (const auto& emp : empleadosOrdenados) {
        cout << left << setw(5) << emp.id
                  << setw(40) << restaurarEspacios(emp.nombres)
                  << setw(40) << restaurarEspacios(emp.apellidos)
                  << setw(20) << emp.faltas
                  << fixed << setprecision(2) << setw(15) << emp.totalHoras << endl;
    }
    cout << "---------------------------------------------------------------------" << endl;
}
