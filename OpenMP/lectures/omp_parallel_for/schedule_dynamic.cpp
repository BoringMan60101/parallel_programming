#include <cstdio>
#include <omp.h> 

int main()
{
    //schedule(тип распред[, unit])
    //сравнить
    // #pragma omp parallel for num_threads(3) schedule(dynamic, 2)
    #pragma omp parallel for num_threads(3) schedule(dynamic)
    for(int i = 0; i < 10; i++)
        printf("id = %d, i = %d\n", omp_get_thread_num(), i);                                       
    return 0;
}
