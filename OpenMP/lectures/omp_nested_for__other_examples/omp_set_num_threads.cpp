#include <cstdio>
#include <omp.h>

int main()
{   
    omp_set_num_threads(4);
    
    #pragma omp parallel num_threads(3)
    {
        printf("Hello, World!\n");
    }
    
    return 0;
}
