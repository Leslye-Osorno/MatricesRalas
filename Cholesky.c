#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// Función para imprimir una matriz
void printMatrix(int n, double** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Método de Cholesky
int choleskyDecomposition(int n, double** A, double** L) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;

            // Calcular sumatoria para L[i][j]
            for (int k = 0; k < j; k++) {
                sum += L[i][k] * L[j][k];
            }

            if (i == j) {
                // Diagonal: L[i][i] = sqrt(A[i][i] - sum)
                double val = A[i][i] - sum;
                if (val <= (1e-9)) {
                    printf("La matriz no es definida positiva.\n");
                    return 0;
                }
                L[i][i] = sqrt(val);
            } else {
                // Fuera de la diagonal: L[i][j] = (A[i][j] - sum) / L[j][j]
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
    return 1;
}

// Resolver Ly = b usando sustitución hacia adelante
void forwardSubstitution(int n, double** L, double* b, double* y) {
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }
}

// Resolver L^T x = y usando sustitución hacia atrás
void backwardSubstitution(int n, double** L, double* y, double* x) {
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += L[j][i] * x[j];
        }
        x[i] = (y[i] - sum) / L[i][i];
    }
}

int main() {
    int n;

    // Ingresar el tamaño de la matriz
    printf("Ingresa el tamaño de la matriz (n): ");
    scanf("%d", &n);

    // Reservar memoria para A, L, b, y y x
    double** A = (double**)malloc(n * sizeof(double*));
    double** L = (double**)malloc(n * sizeof(double*));
    double* b = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(n * sizeof(double));
    double* x = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(n * sizeof(double));
        L[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            L[i][j] = 0;
        }
    }

    // Ingreso manual de la matriz A
    printf("Ingresa los elementos de la matriz A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    // Ingreso manual del vector b
    printf("Ingresa los elementos del vector b:\n");
    for (int i = 0; i < n; i++) {
        printf("b[%d]: ", i);
        scanf("%lf", &b[i]);
    }

    // Realizar la factorización de Cholesky
    if (!choleskyDecomposition(n, A, L)) {
        printf("Error: No se pudo realizar la factorización de Cholesky.\n");
        return 1;
    }

    // Imprimir la matriz L
    printf("Matriz L obtenida de la factorización de Cholesky:\n");
    printMatrix(n, L);

    // Resolver Ly = b
    forwardSubstitution(n, L, b, y);

    // Resolver L^T x = y
    backwardSubstitution(n, L, y, x);

    // Imprimir la solución
    printf("\nSolución del sistema (vector x):\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %lf\n", i, x[i]);
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(L[i]);
    }
    free(A);
    free(L);
    free(b);
    free(y);
    free(x);

    return 0;
}
