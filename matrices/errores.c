#include "errores.h"

// Manejar error de matriz no cuadrada
void handleNonSquareMatrixError(int n, int m) {
    printf("Error: La matriz no es cuadrada (%dx%d).\n", n, m);
}

// Manejar error de matriz no definida positiva
void handleNonPositiveDefiniteMatrixError(int n, Matrix A) {
    printf("Error: La matriz no es definida positiva.\n");
    printMatrix(n, A);
}

// Manejar error de matriz no simétrica
void handleNonSymmetricMatrixError(int n, Matrix A) {
    printf("Error: La matriz no es simétrica.\n");
    printMatrix(n, A);
}

// Manejar error de tamaño de matriz inválido
void handleInvalidMatrixSizeError(int n) {
    printf("Error: El tamaño de la matriz (%d) es inválido.\n", n);
}
