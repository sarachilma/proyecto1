#include <stdio.h>

// Definimos el tamaño de las matrices (N x N)
#define N 3

// Función para multiplicar dos matrices
void multiplicar_matrices(int A[N][N], int B[N][N], int resultado[N][N]) {
    // Recorremos las filas de la matriz A
    for (int i = 0; i < N; i++) {
        // Recorremos las columnas de la matriz B
        for (int j = 0; j < N; j++) {
            // Inicializamos el elemento (i, j) de la matriz resultado en 0
            resultado[i][j] = 0;

            // Realizamos el cálculo del elemento (i, j) de la matriz resultado
            for (int k = 0; k < N; k++) {
                // Sumamos el producto de los elementos correspondientes de A y B
                resultado[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // Definimos dos matrices de entrada (A y B) y una matriz para el resultado
    int A[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[N][N] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int resultado[N][N];

    // Simulamos la activación de un pin de E/S (ponerlo en alto)
    printf("Inicio de la multiplicación de matrices.\n");

    // Llamamos a la función para multiplicar las matrices A y B
    multiplicar_matrices(A, B, resultado);

    // Simulamos la desactivación del pin de E/S (ponerlo en bajo)
    printf("Fin de la multiplicación de matrices.\n");

    // Mostramos el resultado de la multiplicación
    printf("Resultado:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Imprimimos cada elemento de la matriz resultado
            printf("%d ", resultado[i][j]);
        }
        // Salto de línea después de cada fila
        printf("\n");
    }

    return 0;  // Indicar que el programa terminó correctamente
}