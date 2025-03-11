#include <stdio.h>

int main() {
    // Declaración de variables
    int minutos;
    float costo_por_minuto = 45.48;
    float costo_total;

    // Solicitar la duración de la llamada al usuario
    printf("Ingrese la duración de la llamada en minutos: ");
    scanf("%d", &minutos);

    // Calcular el costo total de la llamada
    costo_total = minutos * costo_por_minuto;

    // Mostrar el resultado en pantalla
    printf("El costo de la llamada es: %f pesos\n", costo_total);

    return 0;
}