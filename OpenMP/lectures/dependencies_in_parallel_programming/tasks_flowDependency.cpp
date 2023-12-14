#include <cstdio>
#include <unistd.h>
#include <omp.h>

// Пример синхронизации задач (потоковая зависимость)

int main()
{
    int x{10}; 
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task depend(out:x)
            {
                sleep(1);
                x = 1234;
            }
            
            #pragma omp task depend(in:x)
            {
                printf("x = %d\n", x);
            }
        }
    }
    
    return 0;
}
