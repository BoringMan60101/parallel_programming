#include <cstdio>
#include <omp.h>
#include <cmath>
#define _USE_MATH_DEFINICES

//Выражение для подынтегральной функции
double y_of_x(double x) { return cos(x); }
//double y_of_x(double x) { return 1.0; }

//Численное нахождение интеграла (в параллельном режиме)
//С использованием 'for' и его опции [reduction]
double integral(double Lb, double Rb, int n, double (*func)(double))
{
    const double dx = (Rb - Lb) / n;
    double I = 0.0;
    
    #pragma omp parallel for reduction(+ : I)
    for(int i = 1; i <= n; i++)
    {
        double c = i*dx - 0.5*dx;
        I += func(c) * dx;
    }
    
    return I;
}


int main()
{
    const int n = 10;
    const double a = 0.0, b = M_PI;
    const double dx = (b-a)/n, I_an = 0.0;
    
    //const double a = 0.0, b = 10.0;
    //const double dx = (b-a)/n, I_an = 10.0;
    
    double I = integral(a, b, n, y_of_x);
    
    printf("I_an = %.16f\n", I_an);
    printf("I_approx = %.16f\n", I);
    printf("|I_an - I| = %.16f\n", fabs(I_an - I));
    
    return 0;
}
