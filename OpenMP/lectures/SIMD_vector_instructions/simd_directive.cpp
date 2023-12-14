#include <iostream>

using namespace std;

//compiling with g++ -Wall -fopenmp-simd -fopt-info-vec simd_directive.cpp [-O]

// private variables are different 
int main()
{
    const int N{1024};
    int *a{new int [N]{}}, *b{new int [N]{}}, *c{new int [N]{}};
    
    #pragma omp simd simdlen(8) //compile with -march=native
    for(int i = 0; i < N; i++)
        c[i] = a[i] + b[i];
    
    cout << c[0] << endl;
    
    
    alignas(8) int *p{new int [N]{}};
    #pragma omp simd aligned(p : 8)
    for(int i = 0; i < N; i++)
        c[i] = a[i] + p[i];
    
    cout << c[0] << endl;
    
    
    return 0;
}
