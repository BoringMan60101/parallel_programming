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
            if(false)  //Сравнить выводы при 'true' / 'false'
            {
                printf("id = %d\n", omp_get_thread_num());
            }
        }
    }
    
    return 0;
}

