#include <cstdio>
#include <omp.h>

int main()
{   
    printf("v1: value: %d\n", omp_in_parallel());
    
    #pragma omp parallel num_threads(3)
    {
        printf("v1: in \'pragma\' value: %d\n", omp_in_parallel());
    }
    
    printf("v1: value: %d\n", omp_in_parallel());
    
    // Сравнить два выполнения
    
    printf("\nv2: value: %d\n", omp_in_parallel());
    
    #pragma omp parallel num_threads(3) if(false)
    {
        printf("v2: in \'pragma\' value: %d\n", omp_in_parallel());
    }
    
    printf("v2: value: %d\n", omp_in_parallel());
    
    return 0;
}
