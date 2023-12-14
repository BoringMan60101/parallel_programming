#include <cstdio>

// Compile with g++ -fopt-info-vec -O -fopenmp-simd simd.cpp

#pragma omp declare simd
int f(int x, int y)
{
    return x + y;
}

int main()
{
    const int n{10};
    int a[n], b[n], c[n];
    
    
    for(int i = 0; i < n; i++)
        c[i] = f(a[i], b[i]);
    
    return 0;
}
