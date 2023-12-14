#include <cstdio>
#include <unistd.h>
//#include <omp.h> 

int main()
{
    int x{-1}, y{-2};
    
    #pragma omp parallel num_threads(4) shared(x)
    {
        #pragma omp single
        {
            #pragma omp task // *задача*
            {
                sleep(1);
                x = 123;
                /*
                #pragma omp task
                {
                    sleep(1);
                    y = 456;
                }
                */
            }
            
            #pragma omp task
            {
                sleep(1);
                y = 456;
            }
            
            #pragma omp taskwait //ожидает завершения *задачи*
            printf("x = %d, y = %i\n", x, y);
        }
    }
    
    return 0;
}

