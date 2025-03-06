#ifndef ERRORES_H
#define ERRORES_H

#include "operaciones_basicas.h"

// Función para verificar si una matriz es simétrica y definida positiva
int isSymmetricPositiveDefiniteCOO(MatrixCOO* A);

// Función para manejar errores de matrices no simétricas y definidas positivas
void handleNonSymmetricPositiveDefiniteMatrixError(MatrixCOO* A);

// Función para manejar errores de matrices no cuadradas
void handleNonSquareMatrixError(MatrixCOO* A);

// Función para manejar errores de matrices con elementos no nulos fuera de la diagonal
void handleNonDiagonalNonZeroElementsError(MatrixCOO* A);

#endif
