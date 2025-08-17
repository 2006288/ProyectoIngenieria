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

// Estructuras para almacenar los datos
struct Empleado {
    int id;
    std::string nombres;
    std::string apellidos;
    std::string direccion;
    std::string telefono;
    std::string correo;
};

struct RegistroHoras {
    int id;
    bool esSalida; // false para entrada, true para salida
    std::chrono::system_clock::time_point timestamp;
};

// Estructura para el reporte final
struct ReporteEmpleado {
    int id;
    std::string nombres;
    std::string apellidos;
    int faltas = 0;
    double totalHoras = 0.0;
};

// Prototipos de funciones
void cargarDatos(std::vector<Empleado>& empleados, std::vector<RegistroHoras>& registros);
void registrarDatosPersonales(std::vector<Empleado>& empleados);
void mostrarHorasPorEmpleado(const std::vector<Empleado>& empleados, const std::vector<RegistroHoras>& registros);
void imprimirReportePuntualidad(const std::vector<Empleado>& empleados, const std::vector<RegistroHoras>& registros);
void mostrarMenu();
std::string reemplazarEspacios(std::string texto);
std::string restaurarEspacios(std::string texto);

// Función para convertir partes de fecha/hora a time_point
std::chrono::system_clock::time_point make_timestamp(int anio, int mes, int dia, int hora, int min) {
    std::tm tm = {};
    tm.tm_year = anio - 1900;
    tm.tm_mon = mes - 1;
    tm.tm_mday = dia;
    tm.tm_hour = hora;
    tm.tm_min = min;
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

int main() {
    mostrarMenu();
    return 0;
}

void mostrarMenu() {
    std::vector<Empleado> empleados;
    std::vector<RegistroHoras> registros;
    cargarDatos(empleados, registros);

    int opcion;
    do {
        std::cout << "\n===============================" << std::endl;
        std::cout << "SISTEMA CONTROL DE EMPLEADOS" << std::endl;
        std::cout << "===============================" << std::endl;
        std::cout << "1.- Registrar nuevo empleado" << std::endl;
        std::cout << "2.- Mostrar registros de horas" << std::endl;
        std::cout << "3.- Imprimir reporte de Mejores Empleados" << std::endl;
        std::cout << "0.- Salir" << std::endl;
        std::cout << "===============================" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

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
                std::cout << "Saliendo del sistema." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                break;
        }
    } while (opcion != 0);
}

std::string reemplazarEspacios(std::string texto) {
    std::replace(texto.begin(), texto.end(), ' ', '_');
    return texto;
}

std::string restaurarEspacios(std::string texto) {
    std::replace(texto.begin(), texto.end(), '_', ' ');
    return texto;
}

void cargarDatos(std::vector<Empleado>& empleados, std::vector<RegistroHoras>& registros) {
    std::ifstream archivoEmpleados("empleados.txt");
    std::string linea;
    if (archivoEmpleados.is_open()) {
        while (getline(archivoEmpleados, linea)) {
            std::stringstream ss(linea);
            Empleado emp;
            ss >> emp.id >> emp.nombres >> emp.apellidos >> emp.direccion >> emp.telefono >> emp.correo;
            empleados.push_back(emp);
        }
        archivoEmpleados.close();
    }

    std::ifstream archivoHoras("horas.txt");
    if (archivoHoras.is_open()) {
        while (getline(archivoHoras, linea)) {
            std::stringstream ss(linea);
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
    std::cin.ignore();
    std::cout << "Ingrese los dos Nombres: ";
    getline(std::cin, empleado.nombres);
    std::cout << "Ingrese los dos Apellidos: ";
    getline(std::cin, empleado.apellidos);
    std::cout << "Ingrese la direccion: ";
    getline(std::cin, empleado.direccion);
    std::cout << "Ingrese el telefono: ";
    getline(std::cin, empleado.telefono);
    std::cout << "Ingrese el correo: ";
    getline(std::cin, empleado.correo);
}

void registrarDatosPersonales(std::vector<Empleado>& empleados) {
    Empleado nuevoEmpleado;
    solicitarDatos(nuevoEmpleado);
    nuevoEmpleado.id = empleados.empty() ? 1 : empleados.back().id + 1;

    std::ofstream archivo("empleados.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << nuevoEmpleado.id << " "
                << reemplazarEspacios(nuevoEmpleado.nombres) << " "
                << reemplazarEspacios(nuevoEmpleado.apellidos) << " "
                << reemplazarEspacios(nuevoEmpleado.direccion) << " "
                << nuevoEmpleado.telefono << " "
                << nuevoEmpleado.correo << std::endl;
        std::cout << "Empleado registrado correctamente con ID: " << nuevoEmpleado.id << std::endl;
        archivo.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo empleados.txt para escribir." << std::endl;
    }
}

void mostrarHorasPorEmpleado(const std::vector<Empleado>& empleados, const std::vector<RegistroHoras>& registros) {
    for (const auto& emp : empleados) {
        std::cout << "\n------------------------------------" << std::endl;
        std::cout << "Empleado: " << restaurarEspacios(emp.nombres) << " " << restaurarEspacios(emp.apellidos) << std::endl;
        std::cout << "------------------------------------" << std::endl;

        for (const auto& reg : registros) {
            if (reg.id == emp.id) {
                std::time_t tiempo = std::chrono::system_clock::to_time_t(reg.timestamp);
                std::tm* tm = std::localtime(&tiempo);
                std::cout << "Fecha: " << std::put_time(tm, "%d/%m/%Y") << " | "
                          << "Hora: " << std::put_time(tm, "%H:%M") << " | "
                          << "Estado: " << (reg.esSalida ? "Salida" : "Entrada") << std::endl;
            }
        }
    }
}

void imprimirReportePuntualidad(const std::vector<Empleado>& empleados, const std::vector<RegistroHoras>& registros) {
    std::map<int, ReporteEmpleado> datosReporte;

    // Inicializar datos del reporte con la información del empleado
    for (const auto& emp : empleados) {
        datosReporte[emp.id].id = emp.id;
        datosReporte[emp.id].nombres = emp.nombres;
        datosReporte[emp.id].apellidos = emp.apellidos;
    }

    // Calcular faltas y horas trabajadas
    for (const auto& emp : empleados) {
        std::map<int, std::chrono::system_clock::time_point> primeraEntradaPorDia;
        std::vector<RegistroHoras> registrosEmpleado;

        for (const auto& reg : registros) {
            if (reg.id == emp.id) {
                registrosEmpleado.push_back(reg);
                if (!reg.esSalida) { // Si es una entrada
                    std::time_t tiempo = std::chrono::system_clock::to_time_t(reg.timestamp);
                    std::tm* tm_local = std::localtime(&tiempo);
                    int diaDelAnio = tm_local->tm_yday;

                    if (primeraEntradaPorDia.find(diaDelAnio) == primeraEntradaPorDia.end() || reg.timestamp < primeraEntradaPorDia[diaDelAnio]) {
                        primeraEntradaPorDia[diaDelAnio] = reg.timestamp;
                    }
                }
            }
        }

        // Contar faltas
        for (const auto& par : primeraEntradaPorDia) {
            std::time_t tiempo = std::chrono::system_clock::to_time_t(par.second);
            std::tm* tm_local = std::localtime(&tiempo);
            if (tm_local->tm_hour > 7 || (tm_local->tm_hour == 7 && tm_local->tm_min > 30)) {
                datosReporte[emp.id].faltas++;
            }
        }

        // Calcular horas trabajadas
        std::sort(registrosEmpleado.begin(), registrosEmpleado.end(), [](const RegistroHoras& a, const RegistroHoras& b) {
            return a.timestamp < b.timestamp;
        });

        for (size_t i = 0; i < registrosEmpleado.size(); ++i) {
            if (!registrosEmpleado[i].esSalida) { // Es una entrada
                // Buscar la siguiente salida
                for (size_t j = i + 1; j < registrosEmpleado.size(); ++j) {
                    if (registrosEmpleado[j].esSalida) {
                        auto diff = registrosEmpleado[j].timestamp - registrosEmpleado[i].timestamp;
                        datosReporte[emp.id].totalHoras += std::chrono::duration<double, std::ratio<3600>>(diff).count();
                        i = j; // Avanzar el índice principal para no re-contar
                        break;
                    }
                }
            }
        }
    }

    // Convertir el mapa a un vector para ordenarlo
    std::vector<ReporteEmpleado> empleadosOrdenados;
    for (const auto& par : datosReporte) {
        empleadosOrdenados.push_back(par.second);
    }

    // Ordenar segun el criterio: menos faltas, luego más horas
    std::sort(empleadosOrdenados.begin(), empleadosOrdenados.end(),
              [](const ReporteEmpleado& a, const ReporteEmpleado& b) {
                  if (a.faltas != b.faltas) {
                      return a.faltas < b.faltas; // Menos faltas es mejor
                  }
                  return a.totalHoras > b.totalHoras; // Más horas es mejor
              });

    // Imprimir el reporte
    std::cout << "\n--- Reporte de Mejores Empleados ---" << std::endl;
    std::cout << std::left << std::setw(5) << "ID" << std::setw(40) << "Empleado" << std::setw(40) << "Direccion" << std::setw(20)<< "Faltas" << std::setw(15) << "Horas Trab." << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
    for (const auto& emp : empleadosOrdenados) {
        std::cout << std::left << std::setw(5) << emp.id
                  << std::setw(40) << restaurarEspacios(emp.nombres)
                  << std::setw(40) << restaurarEspacios(emp.apellidos)
                  << std::setw(20) << emp.faltas
                  << std::fixed << std::setprecision(2) << std::setw(15) << emp.totalHoras << std::endl;
    }
    std::cout << "---------------------------------------------------------------------" << std::endl;
}
