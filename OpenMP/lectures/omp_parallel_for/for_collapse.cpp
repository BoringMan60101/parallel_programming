#include <cstdio>
#include <omp.h>

int main()
{

    //Сравнить 2 вывода
    
    //#pragma omp parallel for num_threads(3) 
    #pragma omp parallel for num_threads(3) collapse(2)
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 3; j++)
            printf("id = %d, i = %d, j = %d\n", omp_get_thread_num(), i, j);
    
    return 0;
}
