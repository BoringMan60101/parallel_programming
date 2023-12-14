#include <cstdio>
#include <omp.h>

int main()
{
    const int n = 50;
    int a[n];
    for(int i = 0; i < n; i++)
        a[i] = 1;
    int s{};
    
    // регион critical выполнится всеми потоками, но может
    // выполняться только одним потоком.
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
        #pragma omp critical
            s += a[i];
    
    
    printf("s = %d\n", s);
    return 0;
}
