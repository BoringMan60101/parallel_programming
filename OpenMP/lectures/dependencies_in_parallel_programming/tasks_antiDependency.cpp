#include <cstdio>
#include <unistd.h>
#include <omp.h>

// Пример синхронизации задач (анти зависимость)

int main()
{
    int x{10}; 
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task depend(in:x)
            {
                sleep(1);
                printf("x = %d\n", x);
            }
            
            #pragma omp task depend(out:x)
            {
                x = 1234;
            }
        }
    }
    
    return 0;
}
