#include <stdio.h>  // Incluir la librería estándar de entrada/salida

int main() {
    // Declaración de variables
    float num1, num2;  // Variables para almacenar los dos números
    float suma, resta, multiplicacion, division;  // Variables para almacenar los resultados

    // Solicitar al usuario que ingrese los dos números
    printf("Ingrese el primer número: ");
    scanf("%f", &num1);  // Leer el primer número

    printf("Ingrese el segundo número: ");
    scanf("%f", &num2);  // Leer el segundo número

    // Realizar las operaciones matemáticas
    suma = num1 + num2;           // Suma
    resta = num1 - num2;          // Resta
    multiplicacion = num1 * num2; // Multiplicación
    division = num1 / num2;       // División

    // Mostrar los resultados
    printf("\nResultados:\n");
    printf("Suma: %.2f\n", suma);              // Mostrar la suma
    printf("Resta: %.2f\n", resta);            // Mostrar la resta
    printf("Multiplicación: %.2f\n", multiplicacion);  // Mostrar la multiplicación
    printf("División: %.2f\n", division);      // Mostrar la división

    return 0;  // Indicar que el programa terminó correctamente
}