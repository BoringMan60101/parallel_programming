#include <cstdio>
#include <omp.h>

int main()
{
    printf("Pure \'taskloop\' default threads num\n");
    #pragma omp parallel 
        #pragma omp single
            #pragma omp taskloop 
            for(int i = 0; i < 10; i++)
                printf("i=%d, id = %d\n", i, omp_get_thread_num());
    printf("\n");
    
    printf("\'taskloop with grainsize\' default threads num\n");
    #pragma omp parallel 
        #pragma omp single
            #pragma omp taskloop grainsize(4)
            for(int i = 0; i < 10; i++)
                printf("i=%d, id = %d\n", i, omp_get_thread_num());
    printf("\n");
    
    printf("\'taskloop with num_tasks\' default threads num\n");
    #pragma omp parallel 
        #pragma omp single
            #pragma omp taskloop num_tasks(3)
            for(int i = 0; i < 10; i++)
                printf("i=%d, id = %d\n", i, omp_get_thread_num());
    printf("\n");
    
    printf("\'taskloop with nogrup\' default threads num\n");
    #pragma omp parallel 
        #pragma omp single
            #pragma omp taskloop nogroup // turns off implicit 'taskgroup'
            for(int i = 0; i < 10; i++)
                printf("i=%d, id = %d\n", i, omp_get_thread_num());
    printf("\n");
    
    return 0;
}
