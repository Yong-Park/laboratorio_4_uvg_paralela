// yongbum park
// 20117

#include <iostream>
#include <cmath>
#include <mpi.h>

using namespace std;

double f(double x) {
    return sin(x);  
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        cerr << "Se requieren al menos 2 procesos para ejecutar este programa." << endl;
        MPI_Finalize();
        return 1;
    }

    double a, b;
    int N;

    if (rank == 0) {
        cout << "Ingrese el límite inferior: ";
        cin >> a;
        cout << "Ingrese el límite superior: ";
        cin >> b;
        cout << "Ingrese el número de subintervalos: ";
        cin >> N;
    }

    MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // Inicia el tiempo
    double start_time = MPI_Wtime();

    double integral = 0.0;
    double delta_x = (b - a) / N;

    for (int i = rank; i < N; i += size) {
        double x = a + i * delta_x;
        integral += f(x) * delta_x;
    }

    double local_integral = integral;
    MPI_Reduce(&local_integral, &integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    // Termina el tiempo
    double end_time = MPI_Wtime();

    if (rank == 0) {
        // Calcula el tiempo en segundos
        double seconds = end_time - start_time;

        cout << "Aproximación de la integral: " << integral << endl;
        cout << "Tiempo de ejecución (segundos): " << seconds << endl;
    }

    MPI_Finalize();

    return 0;
}
