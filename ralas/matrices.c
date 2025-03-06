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
    MatrixCOO* A = allocateMatrixCOO(n, n, n * n);
    MatrixCOO* P = allocateMatrixCOO(n, n, n * n);
    MatrixCOO* L = allocateMatrixCOO(n, n, n * n);
    MatrixCOO* U = allocateMatrixCOO(n, n, n * n);
    double* b = (double*)malloc(n * sizeof(double));
    double* x = (double*)malloc(n * sizeof(double));

    // Inicializar matrices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A->row[i * n + j] = i;
            A->col[i * n + j] = j;
            A->val[i * n + j] = i + j;

            P->row[i * n + j] = 0;
            P->col[i * n + j] = 0;
            P->val[i * n + j] = 0;

            L->row[i * n + j] = 0;
            L->col[i * n + j] = 0;
            L->val[i * n + j] = 0;

            U->row[i * n + j] = 0;
            U->col[i * n + j] = 0;
            U->val[i * n + j] = 0;
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
                pluDecompositionCOO(A, P, L, U);
                printf("Factorización PLU:\n");
                printf("P:\n");
                printMatrixCOO(P);
                printf("L:\n");
                printMatrixCOO(L);
                printf("U:\n");
                printMatrixCOO(U);
                break;
            case 2:
                if (choleskyDecompositionCOO(A, L)) {
                    printf("Descomposición de Cholesky:\n");
                    printMatrixCOO(L);
                }
                break;
            case 3:
                conjugateGradientCOO(A, b, x);
                printf("Solución del sistema lineal:\n");
                for (int i = 0; i < n; i++) {
                    printf("%lf\n", x[i]);
                }
                break;
            case 4:
                if (isSymmetricPositiveDefiniteCOO(A)) {
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
    freeMatrixCOO(A);
    freeMatrixCOO(P);
    freeMatrixCOO(L);
    freeMatrixCOO(U);
    free(b);
    free(x);

    return 0;
}
