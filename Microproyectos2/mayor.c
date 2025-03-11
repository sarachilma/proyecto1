#include <stdio.h>  // Incluir la librería estándar de entrada/salida

int main() {
    // Declaración de variables
    int num1, num2, num3;

    // Solicitar al usuario que ingrese los tres números
    printf("Ingrese el primer número: ");
    scanf("%d", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%d", &num2);
    printf("Ingrese el tercer número: ");
    scanf("%d", &num3);

    // Encontrar el mayor de los tres números
    if (num1 > num2 && num1 > num3) {
        printf("El mayor es: %d\n", num1);
    } else if (num2 > num3) {
        printf("El mayor es: %d\n", num2);
    } else {
        printf("El mayor es: %d\n", num3);
    }

    return 0;  // Indicar que el programa terminó correctamente
}