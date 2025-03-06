#ifndef METODOS_LINEALES_H
#define METODOS_LINEALES_H

#include "operaciones_basicas.h"
#include "errores.h"

// Función para realizar la factorización PLU
void pluDecompositionCOO(MatrixCOO* A, MatrixCOO* P, MatrixCOO* L, MatrixCOO* U);

// Función para realizar la descomposición de Cholesky
int choleskyDecompositionCOO(MatrixCOO* A, MatrixCOO* L);

// Función para realizar el método del gradiente conjugado
void conjugateGradientCOO(MatrixCOO* A, double* b, double* x);

#endif
