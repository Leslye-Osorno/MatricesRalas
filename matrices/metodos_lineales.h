#ifndef METODOS_LINEALES_H
#define METODOS_LINEALES_H

#include "operaciones_basicas.h"
#include "errores.h"

// Factorización PLU
void pluDecomposition(int n, Matrix A, Matrix P, Matrix L, Matrix U);

// Descomposición de Cholesky
int choleskyDecomposition(int n, Matrix A, Matrix L);

// Método del Gradiente Conjugado
void conjugateGradient(int n, Matrix A, double* b, double* x);

#endif
