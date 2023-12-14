#include <cstdio>
#include <omp.h>

int main()
{
    #pragma omp parallel
        #pragma omp task
            printf("id = %d\n", omp_get_thread_num());
    //Видно, что один поток может выполнить несколько задач
    return 0;
}
