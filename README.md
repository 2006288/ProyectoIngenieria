# Sistema de Control de Empleados

Este proyecto es un sistema de línea de comandos desarrollado en C++ para gestionar el control de acceso, la puntualidad y las horas trabajadas de los empleados. La aplicación lee los datos desde archivos de texto, procesa la información y presenta un menú interactivo para el usuario.

## Características Principales

- **Registro de Empleados:** Permite añadir nuevos empleados al sistema, los cuales se guardan en `empleados.txt`.
- **Visualización de Registros:** Muestra un historial completo de las entradas y salidas para cada empleado.
- **Reporte de "Mejores Empleados":** Genera un reporte que clasifica a los empleados según dos criterios:
  1.  **Menor número de faltas** por impuntualidad (llegar después de las 07:30).
  2.  **Mayor número de horas trabajadas** (usado como criterio de desempate).

## Requisitos

- Un compilador de C++ compatible con C++11 o superior (ej. g++, Clang, MSVC).

## Archivos de Datos

El programa utiliza dos archivos de texto para persistir la información:

### `empleados.txt`

Almacena la información de los empleados. Cada línea representa un empleado con campos separados por espacios. **Nota:** Los nombres, apellidos y direcciones con espacios se guardan reemplazando los espacios por guiones bajos (`_`).

**Formato:**
`ID Nombres Apellidos Dirección Teléfono Correo`

**Ejemplo:**
`1 Juan_Carlos Perez_Gomez Av_Siempre_Viva_123 5551234 juan.perez@email.com`

### `horas.txt`

Almacena los registros de entrada y salida. `Estado` es `0` para entrada y `1` para salida.

**Formato:**
`ID Estado HH:MM DD/MM/AAAA`

**Ejemplo:**
`1 0 07:25 01/08/2025`
`1 1 17:30 01/08/2025`

## Compilación y Ejecución

1.  **Compilar el programa:**
    Se recomienda usar g++. El siguiente comando genera el ejecutable `SistemaControl.exe`.

    ```bash
    g++ SistemaControl.c++ -o SistemaControl.exe -std=c++11 -static-libgcc -static-libstdc++
    ```

2.  **Ejecutar el programa:**

    ```bash
    ./SistemaControl.exe
    ```

## Uso del Menú

Al ejecutar el programa, se presentará un menú con las siguientes opciones:

- **1.- Registrar nuevo empleado:** Pide por consola los datos de un nuevo empleado y lo añade a `empleados.txt`.
- **2.- Mostrar registros de horas:** Muestra el historial de entradas y salidas de todos los empleados.
- **3.- Imprimir reporte de Mejores Empleados:** Calcula y muestra el reporte de puntualidad y horas trabajadas, ordenado según los criterios definidos.
- **0.- Salir:** Cierra la aplicación.