#include <stdio.h>  // Incluir la librería estándar de entrada/salida

int main() {
    // Declaración de variables
    int primero = 0;  // Primer término de la serie
    int segundo = 1;  // Segundo término de la serie
    int siguiente;    // Siguiente término de la serie

    // Mostrar los dos primeros términos
    printf("Serie de Fibonacci hasta el término <= 1000:\n");
    printf("%d, %d", primero, segundo);

    // Generar la serie hasta que el término sea <= 1000
    siguiente = primero + segundo;
    while (siguiente <= 1000) {
        printf(", %d", siguiente);  // Mostrar el siguiente término
        primero = segundo;         // Actualizar el primer término
        segundo = siguiente;       // Actualizar el segundo término
        siguiente = primero + segundo;  // Calcular el siguiente término
    }

    printf("\n");  // Salto de línea al final

    return 0;  // Indicar que el programa terminó correctamente
}