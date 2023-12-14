#include <cstdio>
#include <omp.h>

int main()
{   
    omp_set_nested(true);
    printf("default max_active_levels: %d\n", omp_get_max_active_levels());
    
    omp_set_max_active_levels(3); //сравнить результаты для '1', '2', '3'
    
    #pragma omp parallel num_threads(2)
    {
        #pragma omp parallel num_threads(2)
        {
            #pragma omp parallel num_threads(2)
            {
                printf("Hello\n");
            }    
        }
    }
    
    return 0;
}
