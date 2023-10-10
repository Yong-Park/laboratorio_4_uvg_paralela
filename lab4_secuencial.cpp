// yongbum park
// 20117

// librerias
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
    if (argc != 4) {
        printf("Uso: %s a b función\n", argv[0]);
        return 1;
    }
    
    double a = atof(argv[1]);     
    double b = atof(argv[2]);     
    int function = atoi(argv[3]); //Indicador de función a integrar
    int n = 10000000;             //Numero de subintervalos

    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock();

    //Calculamos la aproximación de la integral usando la función trapezoides
    double result = trapezoides(a, b, n, function);

    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Con n = %d trapezoides, nuestra aproximacion de la integral de %.6lf a %.6lf es %.13lf\n", n, a, b, result);
    printf("Tiempo de ejecución: %lf segundos\n", cpu_time_used);
    return 0;
}
