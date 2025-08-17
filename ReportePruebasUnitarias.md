# Reporte de Pruebas Unitarias: Sistema de Control de Empleados

## Introducción

Este documento detalla los casos de prueba diseñados para verificar las funcionalidades clave de la aplicación `SistemaControl`, siguiendo un formato estándar para asegurar la calidad y el correcto funcionamiento del software.

## Formato de Caso de Prueba Estándar

- **ID del Caso de Prueba:** Identificador único.
- **Escenario de Prueba:** Descripción de la funcionalidad a probar.
- **Requisitos Previos:** Condiciones que deben cumplirse antes de la ejecución.
- **Datos de Prueba:** Datos de entrada específicos para la prueba.
- **Pasos de Prueba:** Acciones exactas para realizar la prueba.
- **Resultados Esperados:** El resultado anticipado si el software funciona correctamente.
- **Resultados Reales:** El resultado observado tras la ejecución (a completar).
- **Estado de la Prueba:** Pasa / Falla (a completar).

---

## Casos de Prueba Ejecutados

### Caso de Prueba #SC001: Registrar un Nuevo Empleado

- **ID:** #SC001
- **Escenario de Prueba:** Verificar que un nuevo empleado pueda ser registrado correctamente en el sistema.
- **Requisitos Previos:** El archivo `empleados.txt` debe existir.
- **Datos de Prueba:**
    - Nombres: `"Pedro"`, Apellidos: `"Ramirez"`, Dirección: `"Av. Principal 456"`, Teléfono: `"0987654321"`, Correo: `"pedro.ramirez@test.com"`
- **Pasos de Prueba:**
    1. Ejecutar `SistemaControl.exe`.
    2. Seleccionar la opción `1`.
    3. Ingresar los datos de prueba cuando se soliciten.
- **Resultados Esperados:** El sistema muestra el mensaje "Empleado registrado correctamente con ID: X". El archivo `empleados.txt` contiene al final la nueva línea con los datos del empleado.
- **Resultados Reales:** 
- **Estado de la Prueba:** 

---

### Caso de Prueba #SC002: Función de utilidad `reemplazarEspacios`

- **ID:** #SC002
- **Escenario de Prueba:** Verificar que la función reemplace correctamente los espacios por guiones bajos.
- **Requisitos Previos:** N/A (Prueba a nivel de código).
- **Datos de Prueba:** `std::string texto = "Hola Mundo";`
- **Pasos de Prueba:**
    1. Llamar a la función `reemplazarEspacios("Hola Mundo")`.
- **Resultados Esperados:** La función debe devolver la cadena `"Hola_Mundo"`.
- **Resultados Reales:** 
- **Estado de la Prueba:** 

---

### Caso de Prueba #SC003: Lógica principal - Reporte de Mejores Empleados

- **ID:** #SC003
- **Escenario de Prueba:** Verificar que el cálculo de faltas, el cómputo de horas trabajadas y el ordenamiento del reporte funcionen correctamente según la especificación (menos faltas, luego más horas).
- **Requisitos Previos:**
    1. Crear un archivo `empleados.txt` con los datos de prueba.
    2. Crear un archivo `horas.txt` con los datos de prueba.
- **Datos de Prueba:**

    **`empleados.txt`:**
    ```
    1 Ana_Sofia Garcia_Lopez Av_Norte_1 111222 ana.g@test.com
    2 Luis_Miguel Torres_Paz Av_Sur_2 333444 luis.t@test.com
    3 Carlos_Jose Velez_Roca Av_Este_3 555666 carlos.v@test.com
    ```

    **`horas.txt`:**
    ```
    1 0 07:20 01/08/2025
    1 1 17:20 01/08/2025
    2 0 07:45 01/08/2025
    2 1 12:45 01/08/2025
    3 0 07:50 01/08/2025
    3 1 17:50 01/08/2025
    1 0 07:15 02/08/2025
    1 1 18:15 02/08/2025
    ```

- **Pasos de Prueba:**
    1. Ejecutar `SistemaControl.exe`.
    2. Seleccionar la opción `3`.

- **Resultados Esperados:** El sistema debe imprimir en la consola el siguiente reporte, con el orden `Ana`, `Carlos`, `Luis`.
    - **Ana (ID 1):** 0 faltas, 21.00 horas trabajadas (10h el día 1 + 11h el día 2).
    - **Carlos (ID 3):** 1 falta (llegó 07:50), 10.00 horas trabajadas.
    - **Luis (ID 2):** 1 falta (llegó 07:45), 5.00 horas trabajadas.

    **Salida exacta esperada en consola:**
    ```
    --- Reporte de Mejores Empleados ---
    ID   Nombres             Apellidos           Faltas     Horas Trab.    
    ---------------------------------------------------------------------
    1    Ana_Sofia           Garcia_Lopez        0          21.00          
    3    Carlos_Jose         Velez_Roca          1          10.00          
    2    Luis_Miguel         Torres_Paz          1          5.00           
    ---------------------------------------------------------------------
    ```

- **Resultados Reales:** 
- **Estado de la Prueba:**