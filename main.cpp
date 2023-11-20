#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

// Подынтегральная функция
double func(double x) {
    return (1 + x*x) / (1 + x*x*x);
}

// Определенный интеграл методом трапеций
double integrate_trapezoidal(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; ++i) {
        result += f(a + i * h);
    }
    result *= h;
    return result;
}

// Определенный интеграл методом Симпсона
double integrate_simpson(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double result = f(a) + f(b);
    for (int i = 1; i < n; i += 2) {
        result += 4 * f(a + i * h);
    }
    for (int i = 2; i < n - 1; i += 2) {
        result += 2 * f(a + i * h);
    }
    result *= h / 3;
    return result;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    double a = 3.0, b = 4.254;
    double epsilon = 1e-5;
    int n = 2;
    while (true) {
        double result_trapezoidal = integrate_trapezoidal(func, a, b, n);
        double result_simpson = integrate_simpson(func, a, b, n);
        if ((result_trapezoidal - integrate_trapezoidal(func, a, b, 2 * n)) / 3 < epsilon) {
            break;
        }

        if ((result_simpson - integrate_simpson(func, a, b, 2 * n)) / 15 < epsilon) {
            break;
        }

        n *= 2;
    }

    cout << "Результат методом трапеций: " << integrate_trapezoidal(func, a, b, n) << endl;
    cout << "Результат методом Симпсона: " << integrate_simpson(func, a, b, n) << endl;

    return 0;
}
