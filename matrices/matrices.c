#include <stdio.h>
#include "operaciones_basicas.h"
#include "metodos_lineales.h"
#include "errores.h"

int main() {

    /*int n;
    printf("Ingrese el tamaño de la matriz (n): ");
    scanf("%d", &n);

    if (n <= 0) {
        handleInvalidMatrixSizeError(n);
        return 1;
    }*/
    int n = 3;

    // Crear matrices
    Matrix A = allocateMatrix(n);
    Matrix P = allocateMatrix(n);
    Matrix L = allocateMatrix(n);
    Matrix U = allocateMatrix(n);
    double* b = (double*)malloc(n * sizeof(double));
    double* x = (double*)malloc(n * sizeof(double));

    // Inicializar matrices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j;
            P[i][j] = 0;
            L[i][j] = 0;
            U[i][j] = 0;
        }
        b[i] = i + 1;
        x[i] = 0;
    }

    int opcion;
    do {
        printf("Menú de Métodos Lineales:\n");
        printf("1. Factorización PLU\n");
        printf("2. Descomposición de Cholesky\n");
        printf("3. Método del Gradiente Conjugado\n");
        printf("4. Verificar si una matriz es simétrica y definida positiva\n");
        printf("5. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                pluDecomposition(n, A, P, L, U);
                printf("Factorización PLU:\n");
                printf("P:\n");
                printMatrix(n, P);
                printf("L:\n");
                printMatrix(n, L);
                printf("U:\n");
                printMatrix(n, U);
                break;
            case 2:
                if (choleskyDecomposition(n, A, L)) {
                    printf("Descomposición de Cholesky:\n");
                    printMatrix(n, L);
                }
                break;
            case 3:
                conjugateGradient(n, A, b, x);
                printf("Solución del sistema lineal:\n");
                for (int i = 0; i < n; i++) {
                    printf("%lf\n", x[i]);
                }
                break;
            case 4:
                if (isSymmetricPositiveDefinite(n, A)) {
                    printf("La matriz es simétrica y definida positiva.\n");
                } else {
                    printf("La matriz no es simétrica y definida positiva.\n");
                }
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida. Por favor, intente de nuevo.\n");
                break;
        }
    } while (opcion != 5);

    // Liberar memoria
    freeMatrix(n, A);
    freeMatrix(n, P);
    freeMatrix(n, L);
    freeMatrix(n, U);
    free(b);
    free(x);

    return 0;
}
