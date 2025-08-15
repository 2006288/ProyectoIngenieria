
# Reporte de Pruebas Unitarias: Sistema de Control de Empleados

## Introducción

Un caso de prueba en el ámbito de las pruebas de software es un documento que detalla un conjunto de condiciones o pasos diseñados para verificar si una característica o funcionalidad específica de una aplicación de software opera como se espera. Define las entradas, acciones y los resultados esperados para un escenario de prueba concreto, asegurando que el software se comporte correctamente bajo diversas condiciones.

El objetivo principal de la redacción de casos de prueba es garantizar que cada funcionalidad opere según lo previsto y detectar problemas en una fase temprana del ciclo de desarrollo.

## Formato de Caso de Prueba Estándar

Un formato estándar para la redacción de casos de prueba incluye los siguientes elementos:

*   **ID del Caso de Prueba:** Identificador único para el caso de prueba.
*   **Escenario de Prueba:** Descripción del escenario que se está probando.
*   **Pasos de Prueba:** Pasos detallados para ejecutar la prueba.
*   **Requisitos Previos:** Condiciones que deben cumplirse antes de ejecutar la prueba.
*   **Datos de Prueba:** Datos de entrada necesarios para la prueba.
*   **Resultados Esperados/Previstos:** El resultado que se espera obtener después de ejecutar la prueba.
*   **Resultados Reales:** El resultado real obtenido después de ejecutar la prueba.
*   **Estado de la Prueba:** Pasa o Falla.

## Casos de Prueba para SistemaControl

A continuación, se presentan algunos casos de prueba para la aplicación `SistemaControl.c++`.

---

### Caso de Prueba 1: Registrar un Nuevo Empleado

*   **ID del Caso de Prueba:** #SC001
*   **Escenario de Prueba:** Verificar que un nuevo empleado pueda ser registrado correctamente en el sistema.
*   **Pasos de Prueba:**
    1.  Ejecutar el programa `SistemaControl_new.exe`.
    2.  Seleccionar la opción "1.- Registrar nuevo empleado".
    3.  Ingresar los nombres, apellidos, dirección, teléfono y correo del nuevo empleado.
*   **Requisitos Previos:** El archivo `empleados.txt` debe existir.
*   **Datos de Prueba:**
    *   Nombres: "Juan Carlos"
    *   Apellidos: "Perez Gomez"
    *   Dirección: "Calle Falsa 123"
    *   Teléfono: "1234567890"
    *   Correo: "juan.perez@example.com"
*   **Resultados Esperados/Previstos:** El sistema debe mostrar un mensaje de confirmación indicando que el empleado ha sido registrado correctamente con un nuevo ID. El nuevo empleado debe ser añadido al archivo `empleados.txt`.
*   **Resultados Reales:** (Por ser completado durante la ejecución de la prueba)
*   **Estado de la Prueba:** (Por ser completado durante la ejecución de la prueba)

---

### Caso de Prueba 2: Mostrar Registros de Horas

*   **ID del Caso de Prueba:** #SC002
*   **Escenario de Prueba:** Verificar que los registros de horas de los empleados se muestren correctamente.
*   **Pasos de Prueba:**
    1.  Ejecutar el programa `SistemaControl_new.exe`.
    2.  Seleccionar la opción "2.- Mostrar registros de horas".
*   **Requisitos Previos:** Los archivos `empleados.txt` y `horas.txt` deben existir y contener datos.
*   **Datos de Prueba:** N/A
*   **Resultados Esperados/Previstos:** El sistema debe mostrar una lista de todos los empleados y, para cada uno, sus registros de entrada y salida con fecha y hora.
*   **Resultados Reales:** (Por ser completado durante la ejecución de la prueba)
*   **Estado de la Prueba:** (Por ser completado durante la ejecución de la prueba)

---

### Caso de Prueba 3: Imprimir Reporte de Puntualidad

*   **ID del Caso de Prueba:** #SC003
*   **Escenario de Prueba:** Verificar que el reporte de puntualidad se genere y muestre correctamente en formato de tabla.
*   **Pasos de Prueba:**
    1.  Ejecutar el programa `SistemaControl_new.exe`.
    2.  Seleccionar la opción "3.- Imprimir reporte de puntualidad (Mejores Empleados)".
*   **Requisitos Previos:** Los archivos `empleados.txt` y `horas.txt` deben existir y contener datos.
*   **Datos de Prueba:** N/A
*   **Resultados Esperados/Previstos:** El sistema debe mostrar una tabla con los empleados ordenados por número de faltas (de menor a mayor). La tabla debe incluir las columnas: "ID", "Nombres", "Apellidos" y "Faltas".
*   **Resultados Reales:** (Por ser completado durante la ejecución de la prueba)
*   **Estado de la Prueba:** (Por ser completado durante la ejecución de la prueba)

---

## Buenas Prácticas para Escribir Casos de Prueba

*   **Priorizar la claridad y la transparencia:** Los casos de prueba deben ser fáciles de entender.
*   **Centrarse en los requisitos del usuario final:** Las pruebas deben reflejar cómo el usuario interactuará con el sistema.
*   **Evitar la repetición:** No crear casos de prueba redundantes.
*   **Mantener los pasos de prueba lo más mínimos posible:** Ser conciso y directo.
*   **Centrarse en lograr la máxima cobertura de prueba:** Asegurarse de que todas las funcionalidades críticas sean probadas.
*   **Crear casos de prueba que se limpien solos:** Las pruebas no deben dejar datos basura que puedan afectar otras pruebas.
*   **Dar forma a los casos de prueba para pruebas que devuelvan los mismos resultados sin importar quién los ejecute:** Las pruebas deben ser consistentes.
*   **Asegurarse de que las pruebas sean autónomas:** Cada prueba debe ser independiente de las demás.
