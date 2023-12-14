#include <cstdio>
#include <unistd.h>
#include <omp.h> 

int main()
{

    #pragma omp parallel num_threads(8)
    {
        #pragma omp single
        {
            for(int i = 1; i <= 10; i++)
            {
                #pragma omp task priority(i)
                {
                    sleep(1);
                    printf("i = %d, id = %d\n", i, omp_get_thread_num());
                }
            }
        }
    }
    
    return 0;
}

