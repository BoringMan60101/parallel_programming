#include <cstdio>
#include <omp.h> 

int main()
{
    //schedule(тип распред[, unit])
    //сравнить
    // #pragma omp parallel for num_threads(3) (guided, 4)
    #pragma omp parallel for num_threads(3) schedule(guided)
    for(int i = 0; i < 30; i++)
        printf("id = %d, i = %d\n", omp_get_thread_num(), i);                                       
    return 0;
}
