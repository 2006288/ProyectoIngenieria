#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct empleados
{
    string nombres;
    string apellidos;
    string direccion;
    string telefono;
    string correo;
};
string remplazarBlanco(string cadena){
    for (size_t i = 0; i < cadena.length(); i++)
    {
        if(cadena[i] == ' '){
            cadena[i] = '_';
        }
    }
    return cadena;
}
void cargarDatos(vector<empleados> &empleados)
{
    string linea;
    ifstream archivo("empleados.txt");
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string id, nombre1, nombre2, apellido1, apellido2, direccion, correo, telefono;
        getline(ss, id, ' ');
        getline(ss, nombre1, '_');
        getline(ss, nombre2, '_');
        getline(ss, apellido1, '_');
        getline(ss, apellido2, ' ');
        getline(ss, direccion, ' ');
        getline(ss, telefono, ' ');
        getline(ss, correo);
        empleados.push_back({remplazarBlanco(nombre1+" "+nombre2),
                            remplazarBlanco(apellido1+" "+apellido2), direccion, telefono, correo});
    }
    archivo.close();
}
void solicitar_datos(empleados *empleado){
    cin.ignore();
    cout<<"Ingrese sus dos Nombres: ";
    getline(cin,empleado->nombres);
    empleado->nombres = remplazarBlanco(empleado->nombres);
    cout<<"Ingrese su dos Apellidos: ";
    getline(cin,empleado->apellidos);
    empleado->apellidos = remplazarBlanco(empleado->apellidos);
    cout<<"Ingrese su direccion: ";
    getline(cin,empleado->direccion);
    empleado->direccion = remplazarBlanco(empleado->direccion);
    cout<<"Ingrese su telefono: ";
    getline(cin,empleado->telefono);
    cout<<"Ingrese su correo: ";
    getline(cin,empleado->correo);
}

void registrar_datos_personales(int num_empleados)
{
    empleados empleado;
    solicitar_datos(&empleado);
    ofstream archivo("empleados.txt", ios::app);
    if(archivo.is_open()){
        archivo<<to_string(num_empleados+1)<<" "<<empleado.nombres<<"_"
               <<empleado.apellidos<<" "<<empleado.direccion<<" "
               <<empleado.telefono<<" "<<empleado.correo<<endl;
    }else{
        cout<<"No se pudo abrir el archivo"<<endl;
    }
    archivo.close();
}

void carga_horas() {}
void imprimir_mejores_empleados(vector<empleados> empleados)
{
}
void mostrar_Menu()
{
    int opcion;
    vector<empleados> empleados;
    cargarDatos(empleados);
    do{
        cout << "===============================\n";
        cout << "SISTEMA CONTROL DE EMPLEADOS\n";
        cout << "===============================\n";
        cout << "1.- Registrar datos personales\n";
        cout << "2.- Cargar horas\n";
        cout << "3.- Imprimir mejores empleados\n";
        cout << "0.- Salir\n";
        cout << "===============================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion){
        case 1:
            registrar_datos_personales(empleados.size());
            break;
        case 2:
            carga_horas();
            break;
        case 3:
            imprimir_mejores_empleados(empleados);
            break;
        }
    } while (opcion != 0);
}

int main()
{
    mostrar_Menu();
}