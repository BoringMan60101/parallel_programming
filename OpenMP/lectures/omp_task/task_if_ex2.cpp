#include <cstdio>
#include <omp.h> 

int main()
{

    #pragma omp parallel num_threads(8)
    {
        #pragma omp single
        {
            printf("id = %d\n", omp_get_thread_num());
            #pragma omp task \
            if(false) 
            {
                printf("id = %d\n", omp_get_thread_num());
                #pragma omp task // Вероятнее всего будет отложена и выполнится другим потоком
                {
                    printf("id = %d\n", omp_get_thread_num());
                }
            }
        }
    }
    
    return 0;
}

