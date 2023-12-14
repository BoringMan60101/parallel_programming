#include <cstdio>
#include <omp.h>

int main()
{
    #pragma omp parallel for ordered
    for(int i = 0; i < 8; i++)
    {
        printf("not ordered: %d, %d\n", omp_get_thread_num(), i);
        #pragma omp ordered
            printf("ordered: %d, %d\n", omp_get_thread_num(), i);
        
    }
    
    return 0;
}


