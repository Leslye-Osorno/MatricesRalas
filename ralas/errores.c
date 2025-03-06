#include "errores.h"

// Función para verificar si una matriz es simétrica y definida positiva
int isSymmetricPositiveDefiniteCOO(MatrixCOO* A) {
    int n = A->n;
    int nnz = A->nnz;

    // Verificar si la matriz es simétrica
    for (int i = 0; i < nnz; i++) {
        if (A->row[i] != A->col[i]) {
            return 0; // La matriz no es simétrica
        }
    }

    // Verificar si la matriz es definida positiva
    for (int i = 0; i < n; i++) {
        double suma = 0;
        for (int j = 0; j < nnz; j++) {
            if (A->row[j] == i && A->col[j] == i) {
                suma += A->val[j];
            }
        }
        if (suma <= 0) {
            return 0; // La matriz no es definida positiva
        }
    }

    return 1; // La matriz es simétrica y definida positiva
}

// Función para manejar errores de matrices no simétricas y definidas positivas
void handleNonSymmetricPositiveDefiniteMatrixError(MatrixCOO* A) {
    printf("Error: La matriz no es simétrica y definida positiva.\n");
    printf("Matriz:\n");
    printMatrixCOO(A);
    exit(1);
}

// Función para manejar errores de matrices no cuadradas
void handleNonSquareMatrixError(MatrixCOO* A) {
    printf("Error: La matriz no es cuadrada.\n");
    printf("Matriz:\n");
    printMatrixCOO(A);
    exit(1);
}

// Función para manejar errores de matrices con elementos no nulos fuera de la diagonal
void handleNonDiagonalNonZeroElementsError(MatrixCOO* A) {
    printf("Error: La matriz tiene elementos no nulos fuera de la diagonal.\n");
    printf("Matriz:\n");
    printMatrixCOO(A);
    exit(1);
}
