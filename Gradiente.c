#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función para multiplicar una matriz por un vector
void matrixVectorMultiply(int n, double** A, double* x, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = 0;
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
}

// Función para calcular el producto punto entre dos vectores
double dotProduct(int n, double* v1, double* v2) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

// Función para restar dos vectores
void vectorSubtract(int n, double* v1, double* v2, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = v1[i] - v2[i];
    }
}

// Función para sumar dos vectores
void vectorAdd(int n, double* v1, double* v2, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = v1[i] + v2[i];
    }
}

// Función para escalar un vector
void scalarMultiply(int n, double scalar, double* v, double* result) {
    for (int i = 0; i < n; i++) {
        result[i] = scalar * v[i];
    }
}

// Método del gradiente conjugado
void conjugateGradient(int n, double** A, double* b, double* x) {
    double* r = (double*)malloc(n * sizeof(double));
    double* p = (double*)malloc(n * sizeof(double));
    double* Ap = (double*)malloc(n * sizeof(double));
    double alpha, beta, r_old, r_new;

    // Inicializar r = b - Ax y p = r
    matrixVectorMultiply(n, A, x, r);
    vectorSubtract(n, b, r, r);
    for (int i = 0; i < n; i++) {
        p[i] = r[i];
    }

    r_old = dotProduct(n, r, r);

    for (int iter = 0; iter < 100000; iter++) {
        matrixVectorMultiply(n, A, p, Ap);
        alpha = r_old / dotProduct(n, p, Ap);

        // Actualizar x y r
        for (int i = 0; i < n; i++) {
            x[i] += alpha * p[i];
            r[i] -= alpha * Ap[i];
        }

        r_new = dotProduct(n, r, r);

        // Comprobar convergencia
        if (sqrt(r_new) < (1e-6)) {
            printf("Convergencia alcanzada en %d iteraciones.\n", iter + 1);
            break;
        }

        // Actualizar p
        beta = r_new / r_old;
        for (int i = 0; i < n; i++) {
            p[i] = r[i] + beta * p[i];
        }

        r_old = r_new;
    }

    // Liberar memoria
    free(r);
    free(p);
    free(Ap);
}

int main() {
    int n;

    // Ingresar el tamaño del sistema
    printf("Ingresa el tamaño de la matriz (n): ");
    scanf("%d", &n);

    // Reservar memoria dinámica para A, b y x
    double** A = (double**)malloc(n * sizeof(double*));
    double* b = (double*)malloc(n * sizeof(double));
    double* x = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(n * sizeof(double));
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
        x[i] = 0;  // Inicializar x con ceros
    }

    // Resolver el sistema usando el método del gradiente conjugado
    conjugateGradient(n, A, b, x);

    // Imprimir la solución
    printf("\nSolución del sistema (vector x):\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %lf\n", i, x[i]);
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);

    return 0;
}
