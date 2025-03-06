#ifndef ERRORES_H
#define ERRORES_H

#include "operaciones_basicas.h"

// Manejar error de matriz no cuadrada
void handleNonSquareMatrixError(int n, int m);

// Manejar error de matriz no definida positiva
void handleNonPositiveDefiniteMatrixError(int n, Matrix A);

// Manejar error de matriz no simétrica
void handleNonSymmetricMatrixError(int n, Matrix A);

// Manejar error de tamaño de matriz inválido
void handleInvalidMatrixSizeError(int n);

#endif
