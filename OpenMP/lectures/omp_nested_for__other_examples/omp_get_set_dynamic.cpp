#include <cstdio>
#include <omp.h>

int main()
{   
    printf("default \'dynamic threads\' mode:%d\n", omp_get_dynamic());
    
    //omp_set_dynamic(1);
    //изначально запрещено изменять число потоков
    //поэтому при запросе 30000 всё рушится
    
    #pragma omp parallel num_threads(300000)
    {
        #pragma omp master
            omp_get_num_threads();
    }
    
    return 0;
}
