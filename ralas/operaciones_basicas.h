#ifndef OPERACIONES_BASICAS_H
#define OPERACIONES_BASICAS_H

#include <stdio.h>
#include <stdlib.h>

// Definir una estructura para una matriz COO
typedef struct {
    int n, m;
    int nnz; // Número de elementos no nulos
    int* row; // Filas de los elementos no nulos
    int* col; // Columnas de los elementos no nulos
    double* val; // Valores de los elementos no nulos
} MatrixCOO;

// Función para crear una matriz COO
MatrixCOO* allocateMatrixCOO(int n, int m, int nnz);

// Función para liberar una matriz COO
void freeMatrixCOO(MatrixCOO* matrix);

// Función para imprimir una matriz COO
void printMatrixCOO(MatrixCOO* matrix);

// Suma de dos matrices ralas
sparse_matrix* sparseMatrixAdd(int n, sparse_matrix* A, sparse_matrix* B);

// Resta de dos matrices ralas
sparse_matrix* sparseMatrixSubtract(int n, sparse_matrix* A, sparse_matrix* B);

// Multiplicación escalar de un vector
void sparseScalarMultiply(int n, double scalar, double* v, double* result);

// Multiplicación matriz rala por vector
void sparseMatrixVectorMultiply(int n, sparse_matrix* A, double* x, double* result);

// Producto punto entre dos vectores
double sparseDotProduct(int n, double* v1, double* v2);

// Norma de un vector
double sparseVectorNorm(int n, double* v);

// Resolver Ly = b (sustitución hacia adelante)
void sparseForwardSubstitution(int n, sparse_matrix* L, double* b, double* y);

// Resolver L^T x = y (sustitución hacia atrás)
void sparseBackwardSubstitution(int n, sparse_matrix* L, double* y, double* x);

// Inicializar una matriz rala
void initializeSparseMatrix(sparse_matrix* matrix);

#endif
