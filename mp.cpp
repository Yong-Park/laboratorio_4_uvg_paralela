// yongbum park
// 20117

// librerias
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

//Funcion que correra el tipo de ecuacion segun el caso ingresado
double f(double x, int function) {
    switch (function) {
        case 1: //Función x^2
            return x * x;
        case 2: //Función 2x^3
            return 2 * x * x * x;
        case 3: //Función sin(x)
            return sin(x);
        default:
            return 0.0;
    }
}

//Regla Trapezoidal
double trapezoides(double a, double b, int n, int function) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a, function) + f(b, function)); //Sumar los valores en los extremos

    //Sumar los valores en los puntos interiores
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x, function);
    }

    return h * sum;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Uso: %s a b función threads\n", argv[0]);
        return 1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int function = atoi(argv[3]);
    int num_threads = atoi(argv[4]);
    int n = 10000000;

    double start_time = omp_get_wtime();
    
    //Operacion inicial segun ejemplo dado
    double h = (b - a) / n;
    int n_local = n / num_threads;
    double sum_local[num_threads]; //Arreglo global
    double sum_global = 0.0;

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        double a_local = a + thread_id * n_local * h;
        double b_local = a_local + n_local * h;
        double result_local = trapezoides(a_local, b_local, n_local, function);

        sum_local[thread_id] = result_local; //Almacenar el resultado en el arreglo
    }

    //Sumar los resultados para el resultado final
    for (int i = 0; i < num_threads; i++) {
        sum_global += sum_local[i];
    }
    double end_time = omp_get_wtime(); // Fin de la medición de tiempo
    double elapsed_time = end_time - start_time;

    printf("Con n = %d trapezoides y %d threads, nuestra aproximacion de la integral de %.6lf a %.6lf es %.13lf\n", n, num_threads, a, b, sum_global);
    printf("Tiempo de ejecución: %.6lf segundos\n", elapsed_time); // Imprimir tiempo de ejecución

    return 0;
}