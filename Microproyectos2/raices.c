#include <stdio.h>   // Incluir la librería estándar de entrada/salida
#include <math.h>    // Incluir la librería matemática para usar sqrt()

int main() {
    // Declaración de variables
    float a, b, c;          // Coeficientes de la ecuación cuadrática
    float discriminante;    // Discriminante (b² - 4ac)
    float raiz1, raiz2;     // Raíces de la ecuación
    float parteReal, parteImaginaria;  // Partes real e imaginaria para raíces complejas

    // Solicitar al usuario que ingrese los coeficientes
    printf("Ingrese el coeficiente a: ");
    scanf("%f", &a);
    printf("Ingrese el coeficiente b: ");
    scanf("%f", &b);
    printf("Ingrese el coeficiente c: ");
    scanf("%f", &c);

    // Calcular el discriminante
    discriminante = b * b - 4 * a * c;

    // Determinar la naturaleza de las raíces
    if (discriminante > 0) {
        // Dos raíces reales y distintas
        raiz1 = (-b + sqrt(discriminante)) / (2 * a);
        raiz2 = (-b - sqrt(discriminante)) / (2 * a);
        printf("Las raíces son reales y distintas:\n");
        printf("Raíz 1 = %.2f\n", raiz1);
        printf("Raíz 2 = %.2f\n", raiz2);
    } else if (discriminante == 0) {
        // Una raíz real (raíz doble)
        raiz1 = -b / (2 * a);
        printf("Las raíces son reales e iguales:\n");
        printf("Raíz = %.2f\n", raiz1);
    } else {
        // Dos raíces complejas conjugadas
        parteReal = -b / (2 * a);
        parteImaginaria = sqrt(-discriminante) / (2 * a);
        printf("Las raíces son complejas conjugadas:\n");
        printf("Raíz 1 = %.2f + %.2fi\n", parteReal, parteImaginaria);
        printf("Raíz 2 = %.2f - %.2fi\n", parteReal, parteImaginaria);
    }

    return 0;  // Indicar que el programa terminó correctamente
}