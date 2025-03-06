#include "metodos_lineales.h"

// Función para realizar la factorización PLU
void pluDecompositionCOO(MatrixCOO* A, MatrixCOO* P, MatrixCOO* L, MatrixCOO* U) {
    int n = A->n;
    int nnz = A->nnz;

    // Verificar si la matriz es cuadrada
    if (n != A->m) {
        handleNonSquareMatrixError(A);
    }

    // Inicializar las matrices P, L y U
    for (int i = 0; i < nnz; i++) {
        P->row[i] = A->row[i];
        P->col[i] = A->col[i];
        P->val[i] = 1.0;

        L->row[i] = A->row[i];
        L->col[i] = A->col[i];
        L->val[i] = A->val[i];

        U->row[i] = A->row[i];
        U->col[i] = A->col[i];
        U->val[i] = A->val[i];
    }

    // Realizar la factorización PLU
    for (int k = 0; k < n; k++) {
        // Encontrar el elemento máximo en la columna k
        int max_idx = k;
        double max_val = fabs(L->val[k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(L->val[i]) > max_val) {
                max_idx = i;
                max_val = fabs(L->val[i]);
            }
        }

        // Intercambiar las filas k y max_idx
        if (max_idx != k) {
            for (int i = 0; i < nnz; i++) {
                if (L->row[i] == k) {
                    L->row[i] = max_idx;
                } else if (L->row[i] == max_idx) {
                    L->row[i] = k;
                }
            }
        }

        // Actualizar las matrices L y U
        for (int i = k + 1; i < n; i++) {
            double factor = L->val[i] / L->val[k];
            for (int j = 0; j < nnz; j++) {
                if (U->row[j] == i && U->col[j] == k) {
                    U->val[j] -= factor * U->val[k];
                }
            }
            L->val[i] = factor;
        }
    }
}

// Función para realizar la descomposición de Cholesky
int choleskyDecompositionCOO(MatrixCOO* A, MatrixCOO* L) {
    int n = A->n;
    int nnz = A->nnz;

    // Verificar si la matriz es simétrica y definida positiva
    if (!isSymmetricPositiveDefiniteCOO(A)) {
        handleNonSymmetricPositiveDefiniteMatrixError(A);
    }

    // Inicializar la matriz L
    for (int i = 0; i < nnz; i++) {
        L->row[i] = A->row[i];
        L->col[i] = A->col[i];
        L->val[i] = A->val[i];
    }

    // Realizar la descomposición de Cholesky
    for (int k = 0; k < n; k++) {
        // Encontrar el elemento máximo en la columna k
        int max_idx = k;
        double max_val = fabs(L->val[k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(L->val[i]) > max_val) {
                max_idx = i;
                max_val = fabs(L->val[i]);
            }
        }

        // Actualizar la matriz L
        for (int i = k + 1; i < n; i++) {
            double factor = L->val[i] / L->val[k];
            for (int j = 0; j < nnz; j++) {
                if (L->row[j] == i && L->col[j] == k) {
                    L->val[j] -= factor * L->val[k];
                }
            }
            L->val[i] = factor;
        }
    }

    return 1;
}

// Función para realizar el método del gradiente conjugado
void conjugateGradientCOO(MatrixCOO* A, double* b, double* x) {
    int n = A->n;
    int nnz = A->nnz;

    // Inicializar el vector de residuos
    double* r = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        r[i] = b[i];
    }

    // Inicializar el vector de direcciones de conjugación
    double* p = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        p[i] = r[i];
    }

    // Inicializar el vector de soluciones
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    // Realizar el método del gradiente conjugado
    for (int k = 0; k < n; k++) {
        // Calcular el producto de la matriz A y el vector p
        double* Ap = (double*)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) {
            Ap[i] = 0.0;
        }
        for (int i = 0; i < nnz; i++) {
            Ap[A->row[i]] += A->val[i] * p[A->col[i]];
        }

        // Calcular el coeficiente de conjugación
        double alpha = 0.0;
        for (int i = 0; i < n; i++) {
            alpha += r[i] * r[i];
        }
        alpha /= dotProduct(p, Ap);

        // Actualizar el vector de soluciones
        for (int i = 0; i < n; i++) {
            x[i] += alpha * p[i];
        }

        // Actualizar el vector de residuos
        for (int i = 0; i < n; i++) {
            r[i] -= alpha * Ap[i];
        }

        // Calcular el coeficiente de conjugación para el próximo paso
        double beta = 0.0;
        for (int i = 0; i < n; i++) {
            beta += r[i] * r[i];
        }
        beta /= alpha;

        // Actualizar el vector de direcciones de conjugación
        for (int i = 0; i < n; i++) {
            p[i] = r[i] + beta * p[i];
        }

        // Liberar memoria
        free(Ap);
    }

    // Liberar memoria
    free(r);
    free(p);
}
