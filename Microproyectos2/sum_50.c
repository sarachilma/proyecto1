#include <stdio.h>  // Incluir la librería estándar de entrada/salida

int main() {
    // Declaración de variables
    int suma = 0;  // Variable para almacenar la suma acumulada

    // Bucle para sumar los primeros 50 números
    for (int i = 1; i <= 50; i++) {
        suma += i;  // Acumular la suma
    }

    // Mostrar el resultado
    printf("La suma de los primeros 50 números es: %d\n", suma);

    return 0;  // Indicar que el programa terminó correctamente
}