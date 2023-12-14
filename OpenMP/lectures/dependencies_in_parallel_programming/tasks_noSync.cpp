#include <cstdio>
#include <unistd.h>
#include <omp.h>

// Пример выполнения не синхронизированных задач

int main()
{
    int x{10}; 
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                sleep(1);
                x = 1234;
            }
            
            #pragma omp task
            {
                printf("x = %d\n", x);
            }
        }
    }
    
    return 0;
}
