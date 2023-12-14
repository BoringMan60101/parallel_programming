#include <cstdio>
#include <omp.h> 

// Директива untied сообщает, что 
// задача может выполняться разными потоками, если она несколько раз останавливается.

int main()
{

    #pragma omp parallel num_threads(8)
    {
        #pragma omp single
        {
            printf("id = %d\n", omp_get_thread_num());
            #pragma omp task untied 
                printf("id = %d\n", omp_get_thread_num());
        }
    }
    
    return 0;
}
