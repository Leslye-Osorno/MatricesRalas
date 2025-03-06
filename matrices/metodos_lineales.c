#include "metodos_lineales.h"

// Factorización PLU
void pluDecomposition(int n, Matrix A, Matrix P, Matrix L, Matrix U) {
    if (n <= 0) {
        handleInvalidMatrixSizeError(n);
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            P[i][j] = (i == j) ? 1.0 : 0.0;
            L[i][j] = 0.0;
            U[i][j] = A[i][j];
        }
        L[i][i] = 1.0;
    }
    
    for (int k = 0; k < n; k++) {
        int pivot = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(U[i][k]) > fabs(U[pivot][k])) {
                pivot = i;
            }
        }
        if (pivot != k) {
            double* temp = U[k];
            U[k] = U[pivot];
            U[pivot] = temp;
            
            temp = P[k];
            P[k] = P[pivot];
            P[pivot] = temp;
        }
        
        for (int i = k + 1; i < n; i++) {
            L[i][k] = U[i][k] / U[k][k];
            for (int j = k; j < n; j++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
    }
}

// Descomposición de Cholesky
int choleskyDecomposition(int n, Matrix A, Matrix L) {
    if (n <= 0) {
        handleInvalidMatrixSizeError(n);
        return 0;
    }

    if (!isSymmetricPositiveDefinite(n, A)) {
        handleNonSymmetricPositiveDefiniteMatrixError(n, A);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;
            for (int k = 0; k < j; k++) {
                sum += L[i][k] * L[j][k];
            }
            if (i == j) {
                double val = A[i][i] - sum;
                if (val <= 1e-9) {
                    handleNonPositiveDefiniteMatrixError(n, A);
                    return 0;
                }
                L[i][i] = sqrt(val);
            } else {
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
    return 1;
}

// Método del Gradiente Conjugado
void conjugateGradient(int n, Matrix A, double* b, double* x) {
    if (n <= 0) {
        handleInvalidMatrixSizeError(n);
        return;
    }

    if (!isSymmetricPositiveDefinite(n, A)) {
        handleNonSymmetricPositiveDefiniteMatrixError(n, A);
        return;
    }

    double* r = (double*)malloc(n * sizeof(double));
    double* p = (double*)malloc(n * sizeof(double));
    double* Ap = (double*)malloc(n * sizeof(double));
    double alpha, beta, r_old, r_new;

    matrixVectorMultiply(n, A, x, r);
    vectorSubtract(n, b, r, r);
    for (int i = 0; i < n; i++) {
        p[i] = r[i];
    }

    r_old = dotProduct(n, r, r);

    for (int iter = 0; iter < 100000; iter++) {
        matrixVectorMultiply(n, A, p, Ap);
        alpha = r_old / dotProduct(n, p, Ap);

        for (int i = 0; i < n; i++) {
            x[i] += alpha * p[i];
            r[i] -= alpha * Ap[i];
        }

        r_new = dotProduct(n, r, r);
        if (sqrt(r_new) < 1e-6) {
            printf("Convergencia alcanzada en %d iteraciones.\n", iter + 1);
            break;
        }

        beta = r_new / r_old;
        for (int i = 0; i < n; i++) {
            p[i] = r[i] + beta * p[i];
        }
        r_old = r_new;
    }

    free(r);
    free(p);
    free(Ap);
}
