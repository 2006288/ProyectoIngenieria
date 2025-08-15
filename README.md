# Sistema de Control de Empleados

Este es un sencillo sistema de línea de comandos para gestionar empleados y sus horas de trabajo. La aplicación está escrita en C++ y permite registrar nuevos empleados, mostrar sus registros de horas y generar un reporte de puntualidad.

## Características

*   Registrar nuevos empleados.
*   Mostrar registros de horas de entrada y salida por empleado.
*   Generar un reporte de puntualidad que muestra a los empleados con menos faltas.

## Requisitos

*   Un compilador de C++ (como g++).

## Instalación y Ejecución

1.  **Compilar el programa:**

    ```bash
    g++ -o SistemaControl.exe SistemaControl.c++
    ```

2.  **Ejecutar el programa:**

    ```bash
    ./SistemaControl.exe
    ```

## Uso

Una vez que el programa esté en ejecución, se mostrará un menú con las siguientes opciones:

*   **1.- Registrar nuevo empleado:** Solicita los datos de un nuevo empleado y lo guarda en `empleados.txt`.
*   **2.- Mostrar registros de horas:** Muestra los registros de entrada y salida de todos los empleados, leyendo los datos de `empleados.txt` y `horas.txt`.
*   **3.- Imprimir reporte de puntualidad (Mejores Empleados):** Genera un reporte que muestra a los empleados ordenados por su número de faltas (llegadas tarde).
*   **0.- Salir:** Termina la ejecución del programa.

### Archivos de Datos

*   `empleados.txt`: Almacena la información de los empleados. Cada línea representa un empleado con el siguiente formato:

    ```
    ID Nombres Apellidos Dirección Teléfono Correo
    ```

*   `horas.txt`: Almacena los registros de horas de los empleados. Cada línea representa un registro con el siguiente formato:

    ```
    ID Estado Hora:Min Dia/Mes/Año
    ```

    Donde `Estado` es `0` para entrada y `1` para salida.
