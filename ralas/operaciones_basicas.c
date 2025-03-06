#include "operaciones_basicas.h"

// Función para crear una matriz COO
MatrixCOO* allocateMatrixCOO(int n, int m, int nnz) {
    MatrixCOO* matrix = (MatrixCOO*)malloc(sizeof(MatrixCOO));
    matrix->n = n;
    matrix->m = m;
    matrix->nnz = nnz;
    matrix->row = (int*)malloc(nnz * sizeof(int));
    matrix->col = (int*)malloc(nnz * sizeof(int));
    matrix->val = (double*)malloc(nnz * sizeof(double));
    return matrix;
}

// Función para liberar una matriz COO
void freeMatrixCOO(MatrixCOO* matrix) {
    free(matrix->row);
    free(matrix->col);
    free(matrix->val);
    free(matrix);
}

// Función para imprimir una matriz COO
void printMatrixCOO(MatrixCOO* matrix) {
    for (int i = 0; i < matrix->nnz; i++) {
        printf("(%d, %d) = %lf\n", matrix->row[i], matrix->col[i], matrix->val[i]);
    }
}

// Suma de dos matrices ralas
MatrixCOO* sparseMatrixAdd(int n, MatrixCOO* A, MatrixCOO* B) {
    MatrixCOO* C = allocateMatrixCOO(n, n, A->nnz + B->nnz);
    int k = 0;
    for (int i = 0; i < A->nnz; i++) {
        C->row[k] = A->row[i];
        C->col[k] = A->col[i];
        C->val[k] = A->val[i];
        k++;
    }
    for (int i = 0; i < B->nnz; i++) {
        C->row[k] = B->row[i];
        C->col[k] = B->col[i];
        C->val[k] = B->val[i];
        k++;
    }
    return C;
}

// Resta de dos matrices ralas
MatrixCOO* sparseMatrixSubtract(int n, MatrixCOO* A, MatrixCOO* B) {
    MatrixCOO* C = allocateMatrixCOO(n, n, A->nnz + B->nnz);
    int k = 0;
    for (int i = 0; i < A->nnz; i++) {
        C->row[k] = A->row[i];
        C->col[k] = A->col[i];
        C->val[k] = A->val[i];
        k++;
    }
    for (int i = 0; i < B->nnz; i++) {
        C->row[k] = B->row[i];
        C->col[k] = B->col[i];
        C->val[k] = -B->val[i];
        k++;
    }
    return C;
}

// Multiplicación escalar de un vector
void sparseScalarMultiply(int n, double scalar, double* v, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = scalar * v[i];
    }
}

// Multiplicación matriz rala por vector
void sparseMatrixVectorMultiply(int n, MatrixCOO* A, double* x, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = 0;
        for (int j = 0; j < A->nnz; j++) {
            if (A->row[j] == i) {
                result[i] += A->val[j] * x[A->col[j]];
            }
        }
    }
}

// Producto punto entre dos vectores
double sparseDotProduct(int n, double* v1, double* v2) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

// Norma de un vector
double sparseVectorNorm(int n, double* v) {
    return sqrt(sparseDotProduct(n, v, v));
}

// Resolver Ly = b (sustitución hacia adelante)
void sparseForwardSubstitution(int n, MatrixCOO* L, double* b, double* y) {
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < L->nnz; j++) {
            if (L->row[j] == i && L->col[j] < i) {
                y[i] -= L->val[j] * y[L->col[j]];
            }
        }
        y[i] /= L->val[L->nnz - 1 - i];
    }
}

// Resolver L^T x = y (sustitución hacia atrás)
void sparseBackwardSubstitution(int n, MatrixCOO* L, double* y, double* x) {
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = 0; j < L->nnz; j++) {
            if (L->row[j] == i && L->col[j] > i) {
                x[i] -= L->val[j] * x[L->col[j]];
            }
        }
        x[i] /= L->val[L->nnz - 1 - i];
    }
}

// Inicializar una matriz rala
void initializeSparseMatrix(MatrixCOO* matrix) {
    matrix->n = 0;
    matrix->m = 0;
    matrix->nnz = 0;
    matrix->row = NULL;
    matrix->col = NULL;
    matrix->val = NULL;
}


