#include "operaciones_basicas.h"

// Función para crear una matriz
Matrix allocateMatrix(int n) {
    Matrix matrix = (Matrix)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

// Función para liberar una matriz
void freeMatrix(int n, Matrix matrix) {
    if (matrix != NULL) {
        for (int i = 0; i < n; i++) {
            if (matrix[i] != NULL) {
                free(matrix[i]);
            }
        }
        free(matrix);
    }
}

// Función para imprimir una matriz
void printMatrix(int n, Matrix matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Suma de dos matrices
Matrix matrixAdd(int n, Matrix A, Matrix B) {
    Matrix result = allocateMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Resta de dos matrices
Matrix matrixSubtract(int n, Matrix A, Matrix B) {
    Matrix result = allocateMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Suma de dos vectores
void vectorAdd(int n, double* v1, double* v2, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = v1[i] + v2[i];
    }
}

// Resta de dos vectores
void vectorSubtract(int n, double* v1, double* v2, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = v1[i] - v2[i];
    }
}

// Multiplicación escalar de un vector
void scalarMultiply(int n, double scalar, double* v, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = scalar * v[i];
    }
}

// Multiplicación matriz por vector
void matrixVectorMultiply(int n, Matrix A, double* x, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = 0;
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
}

// Producto punto entre dos vectores
double dotProduct(int n, double* v1, double* v2) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

// Norma de un vector
double vectorNorm(int n, double* v) {
    return sqrt(dotProduct(n, v, v));
}

// Resolver Ly = b (sustitución hacia adelante)
void forwardSubstitution(int n, Matrix L, double* b, double* y) {
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }
}

// Resolver L^T x = y (sustitución hacia atrás)
void backwardSubstitution(int n, Matrix L, double* y, double* x) {
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += L[j][i] * x[j];
        }
        x[i] = (y[i] - sum) / L[i][i];
    }
}
