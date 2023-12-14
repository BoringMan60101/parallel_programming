#include <cstdio>
#include <unistd.h>
#include <omp.h>

// Пример синхронизации задач 

int main()
{
    int x{10}; 
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task depend(out:x)
            {
                x = 111;
            }
            
            #pragma omp task depend(out:x)
            {
                x = 222;
            }
            
            #pragma omp taskwait
            printf("x = %d\n", x);
        }
    }
    
    return 0;
}
