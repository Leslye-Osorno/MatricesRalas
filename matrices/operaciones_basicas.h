#ifndef OPERACIONES_BASICAS_H
#define OPERACIONES_BASICAS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double** Matrix;

// Función para crear una matriz
Matrix allocateMatrix(int n);

// Función para liberar una matriz
void freeMatrix(int n, Matrix matrix);

// Función para imprimir una matriz
void printMatrix(int n, Matrix matrix);

// Suma de dos matrices
Matrix matrixAdd(int n, Matrix A, Matrix B);

// Resta de dos matrices
Matrix matrixSubtract(int n, Matrix A, Matrix B);

// Suma de dos vectores
void vectorAdd(int n, double* v1, double* v2, double* result);

// Resta de dos vectores
void vectorSubtract(int n, double* v1, double* v2, double* result);

// Multiplicación escalar de un vector
void scalarMultiply(int n, double scalar, double* v, double* result);

// Multiplicación matriz por vector
void matrixVectorMultiply(int n, Matrix A, double* x, double* result);

// Producto punto entre dos vectores
double dotProduct(int n, double* v1, double* v2);

// Norma de un vector
double vectorNorm(int n, double* v);

// Resolver Ly = b (sustitución hacia adelante)
void forwardSubstitution(int n, Matrix L, double* b, double* y);

// Resolver L^T x = y (sustitución hacia atrás)
void backwardSubstitution(int n, Matrix L, double* y, double* x);

#endif
