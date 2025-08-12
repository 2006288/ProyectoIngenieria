#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Estructura EMPLEADO según los requisitos
struct EMPLEADO {
    string nombre;           // 60 caracteres max
    string direccion;        // 100 caracteres max
    string telefono;         // 9 caracteres
    string email;            // 20 caracteres max
    int faltas_puntualidad;  // Número de faltas por impuntualidad
    double horas_trabajadas; // Total de horas trabajadas en el año
    
    // Constructor para inicializar valores
    EMPLEADO() : faltas_puntualidad(0), horas_trabajadas(0.0) {}
};

// Función para convertir string de hora a minutos desde medianoche
int horaAMinutos(const string& hora) {
    int pos = hora.find(':');
    int horas = stoi(hora.substr(0, pos));
    int minutos = stoi(hora.substr(pos + 1));
    return horas * 60 + minutos;
}

// Función para convertir minutos a horas decimales
double minutosAHoras(int minutos) {
    return minutos / 60.0;
}

// Función 1: registrar_datos_personales
vector<EMPLEADO>* registrar_datos_personales(int& num_empleados) {
    ifstream archivo("empleados.txt");
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo empleados.txt" << endl;
        num_empleados = 0;
        return nullptr;
    }
    
    // Leer el número de empleados
    archivo >> num_empleados;
    archivo.ignore(); // Ignorar el salto de línea
    
    // Reservar memoria dinámica para la tabla de empleados
    vector<EMPLEADO>* empleados = new vector<EMPLEADO>(num_empleados);
    
    string linea;
    for (int i = 0; i < num_empleados; i++) {
        if (getline(archivo, linea)) {
            stringstream ss(linea);
            string campo;
            
            // Leer nombre (reemplazar guiones bajos por espacios)
            ss >> (*empleados)[i].nombre;
            replace((*empleados)[i].nombre.begin(), (*empleados)[i].nombre.end(), '_', ' ');
            
            // Leer dirección (reemplazar guiones bajos por espacios)
            ss >> (*empleados)[i].direccion;
            replace((*empleados)[i].direccion.begin(), (*empleados)[i].direccion.end(), '_', ' ');
            
            // Leer teléfono
            ss >> (*empleados)[i].telefono;
            
            // Leer email
            ss >> (*empleados)[i].email;
        }
    }
    
    archivo.close();
    cout << "Datos personales registrados exitosamente. Total empleados: " << num_empleados << endl;
    return empleados;
}

// Función 2: carga_horas
void carga_horas(vector<EMPLEADO>* empleados, int num_empleados) {
    if (!empleados || num_empleados == 0) {
        cout << "Error: Primero debe registrar los datos personales" << endl;
        return;
    }
    
    ifstream archivo("horas.txt");
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo horas.txt" << endl;
        return;
    }
    
    // Vector para almacenar las horas de entrada de cada empleado por día
    vector<vector<int>> entradas(num_empleados);
    vector<vector<int>> salidas(num_empleados);
    
    int id_empleado, tipo_registro;
    string hora, fecha;
    
    while (archivo >> id_empleado >> tipo_registro >> hora >> fecha) {
        if (id_empleado >= 0 && id_empleado < num_empleados) {
            int minutos = horaAMinutos(hora);
            
            if (tipo_registro == 0) { // Entrada
                entradas[id_empleado].push_back(minutos);
                
                // Verificar puntualidad (07:30 = 7*60 + 30 = 450 minutos)
                if (minutos > 450) { // Llegada después de las 07:30
                    (*empleados)[id_empleado].faltas_puntualidad++;
                }
            } else if (tipo_registro == 1) { // Salida
                salidas[id_empleado].push_back(minutos);
            }
        }
    }
    
    // Calcular horas trabajadas para cada empleado
    for (int i = 0; i < num_empleados; i++) {
        double total_horas = 0.0;
        
        // Emparejar entradas con salidas
        int min_registros = min(entradas[i].size(), salidas[i].size());
        
        for (int j = 0; j < min_registros; j++) {
            // Calcular diferencia en minutos y convertir a horas
            int diferencia_minutos = salidas[i][j] - entradas[i][j];
            if (diferencia_minutos > 0) { // Solo contar si la salida es después de la entrada
                total_horas += minutosAHoras(diferencia_minutos);
            }
        }
        
        (*empleados)[i].horas_trabajadas = total_horas;
    }
    
    archivo.close();
    cout << "Horas cargadas exitosamente." << endl;
}

// Función 3: imprime_mejores_empleados
void imprime_mejores_empleados(vector<EMPLEADO>* empleados, int num_empleados) {
    if (!empleados || num_empleados == 0) {
        cout << "Error: No hay empleados registrados" << endl;
        return;
    }
    
    // Crear vector de índices para ordenar
    vector<int> indices;
    for (int i = 0; i < num_empleados; i++) {
        indices.push_back(i);
    }
    
    // Ordenar por faltas (ascendente) y por horas trabajadas (descendente)
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        if ((*empleados)[a].faltas_puntualidad != (*empleados)[b].faltas_puntualidad) {
            return (*empleados)[a].faltas_puntualidad < (*empleados)[b].faltas_puntualidad;
        }
        return (*empleados)[a].horas_trabajadas > (*empleados)[b].horas_trabajadas;
    });
    
    cout << "\n=== MEJORES EMPLEADOS ===" << endl;
    cout << "Ordenados por menor número de faltas y mayor horas trabajadas" << endl;
    cout << string(80, '-') << endl;
    cout << setw(4) << "ID" << setw(25) << "NOMBRE" << setw(10) << "FALTAS" 
         << setw(15) << "HORAS TRAB." << endl;
    cout << string(80, '-') << endl;
    
    for (int i = 0; i < num_empleados; i++) {
        int idx = indices[i];
        cout << setw(4) << idx 
             << setw(25) << (*empleados)[idx].nombre.substr(0, 24)
             << setw(10) << (*empleados)[idx].faltas_puntualidad
             << setw(15) << fixed << setprecision(2) << (*empleados)[idx].horas_trabajadas
             << endl;
    }
    cout << string(80, '-') << endl;
}

// Función para mostrar el menú principal
void mostrarMenu() {
    cout << "\n=== SISTEMA DE CONTROL DE ACCESO DE EMPLEADOS ===" << endl;
    cout << "1. Registrar Datos Personales" << endl;
    cout << "2. Cargar Horas" << endl;
    cout << "3. Imprimir Mejores Empleados" << endl;
    cout << "4. Mostrar Todos los Empleados" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opción: ";
}

// Función adicional para mostrar todos los empleados
void mostrar_empleados(vector<EMPLEADO>* empleados, int num_empleados) {
    if (!empleados || num_empleados == 0) {
        cout << "Error: No hay empleados registrados" << endl;
        return;
    }
    
    cout << "\n=== LISTA COMPLETA DE EMPLEADOS ===" << endl;
    for (int i = 0; i < num_empleados; i++) {
        cout << "\nEmpleado #" << i << ":" << endl;
        cout << "  Nombre: " << (*empleados)[i].nombre << endl;
        cout << "  Dirección: " << (*empleados)[i].direccion << endl;
        cout << "  Teléfono: " << (*empleados)[i].telefono << endl;
        cout << "  Email: " << (*empleados)[i].email << endl;
        cout << "  Faltas de puntualidad: " << (*empleados)[i].faltas_puntualidad << endl;
        cout << "  Horas trabajadas: " << fixed << setprecision(2) 
             << (*empleados)[i].horas_trabajadas << endl;
        cout << string(50, '-') << endl;
    }
}

// Programa principal con menú
int main() {
    vector<EMPLEADO>* empleados = nullptr;
    int num_empleados = 0;
    int opcion;
    
    cout << "=== BIENVENIDO AL SISTEMA DE CONTROL DE ACCESO ===" << endl;
    
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                // Liberar memoria anterior si existe
                if (empleados != nullptr) {
                    delete empleados;
                }
                empleados = registrar_datos_personales(num_empleados);
                break;
                
            case 2:
                carga_horas(empleados, num_empleados);
                break;
                
            case 3:
                imprime_mejores_empleados(empleados, num_empleados);
                break;
                
            case 4:
                mostrar_empleados(empleados, num_empleados);
                break;
                
            case 5:
                cout << "Saliendo del sistema..." << endl;
                break;
                
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
        }
        
        if (opcion != 5) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while (opcion != 5);
    
    // Liberar memoria antes de salir
    if (empleados != nullptr) {
        delete empleados;
    }
    
    return 0;
}