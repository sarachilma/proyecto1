#include <stdio.h>

int main() {
    // Declaración de la variable para almacenar la nota
    float nota;

    // Solicitar la nota al usuario
    printf("Ingrese la nota de la asignatura (entre 0.0 y 5.0): ");
    scanf("%f", &nota);

    // Verificar si la nota es incorrecta
    while (nota < 0.0 || nota > 5.0) {
        // Mostrar mensaje de error
        printf("ERROR: Nota incorrecta, debe ser >= 0.0 y <= 5.0\n");

        // Volver a solicitar la nota
        printf("Ingrese la nota de la asignatura (entre 0.0 y 5.0): ");
        scanf("%f", &nota);
    }

    // Determinar si el estudiante está aprobado o suspendido
    if (nota >= 3.0) {
        printf("APROBADO\n");
    } else {
        printf("SUSPENDIDO\n");
    }

    return 0;
}