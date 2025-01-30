#include <stdio.h>
#include <stdlib.h>

void luDecomposition(float** A, float** L, float** U, int N) {
    int i, j, k;

    // Inicializando L y U
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == j)
                L[i][j] = 1;
            else
                L[i][j] = 0;
            U[i][j] = 0;
        }
    }

    // Proceso de factorización LU
    for (j = 0; j < N; j++) {
        for (i = 0; i <= j; i++) {
            U[i][j] = A[i][j];
            for (k = 0; k < i; k++)
                U[i][j] -= L[i][k] * U[k][j];
        }
        for (i = j + 1; i < N; i++) {
            L[i][j] = A[i][j];
            for (k = 0; k < j; k++)
                L[i][j] -= L[i][k] * U[k][j];
            L[i][j] /= U[j][j];
        }
    }
}

void printMatrix(float** M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", M[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N;

    // Ingresar el tamaño de la matriz
    printf("Ingresa el tamaño de la matriz A(nxn): ");
    scanf("%d", &N);

    // Reservar memoria dinámica para las matrices A, L y U
    float** A = (float**) malloc(N * sizeof(float*));
    float** L = (float**) malloc(N * sizeof(float*));
    float** U = (float**) malloc(N * sizeof(float*));
    for (int i = 0; i < N; i++) {
        A[i] = (float*) malloc(N * sizeof(float));
        L[i] = (float*) malloc(N * sizeof(float));
        U[i] = (float*) malloc(N * sizeof(float));
    }

    // Ingreso manual de la matriz A
    printf("Ingresa los elementos de la matriz A (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%f", &A[i][j]);
        }
    }

    // Factorización LU
    luDecomposition(A, L, U, N);

    // Imprimir matrices L y U
    printf("\nMatriz L:\n");
    printMatrix(L, N);
    printf("\nMatriz U:\n");
    printMatrix(U, N);

    // Liberar memoria
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(L);
    free(U);

    return 0;
}
