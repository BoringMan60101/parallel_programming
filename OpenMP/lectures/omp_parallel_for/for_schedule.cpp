#include <cstdio>
#include <omp.h>

int main()
{

    //Сравнить 2 вывода
    
    //#pragma omp parallel for num_threads(2) schedule(static, 2)
    #pragma omp parallel for num_threads(2) schedule(static)
    for(int i = 0; i < 10; i++)
        printf("id = %d, i = %d\n", omp_get_thread_num(), i);
    
    return 0;
}
