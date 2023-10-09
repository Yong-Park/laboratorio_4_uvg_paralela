#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

// Función que defines para calcular la función que quieres integrar.
double f(double x) {
    return sin(x);  
}

int main() {
    double a, b;
    int N;

    cout << "Ingrese el límite inferior: ";
    cin >> a;
    cout << "Ingrese el límite superior: ";
    cin >> b;
    cout << "Ingrese el número de subintervalos: ";
    cin >> N;

    // Inicia el cronómetro
    auto start_time = chrono::high_resolution_clock::now();

    double integral = 0.0;
    double delta_x = (b - a) / N;

    for (int i = 0; i < N; ++i) {
        double x = a + i * delta_x;
        integral += f(x) * delta_x;
    }

    // Detiene el cronómetro
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    // Convierte la duración a segundos
    double seconds = duration.count() / 1e6;

    cout << "Aproximación de la integral: " << integral << endl;
    cout << "Tiempo de ejecución (segundos): " << seconds << endl;

    return 0;
}
