#include <cstdio>
#include <omp.h>

int main()
{   
    omp_set_nested(true);
    
    //#pragma omp parallel num_threads(3) if(false)
    #pragma omp parallel num_threads(3) 
    {
        #pragma omp parallel num_threads(2)
        {
            #pragma omp single
            {
                printf("levels = %d \n", omp_get_level()); // сколько вложенных регионов
                
                printf("avtive levels = %d \n", omp_get_active_level()); // глубина активных вложенных регионов
                
                printf("id = %d \n", omp_get_ancestor_thread_num(1)); // номер потока с заданного уровня
                
                printf("size = %d \n", omp_get_team_size(1)); // кол-во потоков на заданном уровне
            }
        }
    }
    
    /*
    
    #pragma omp parallel num_threads(3)
    {
        #pragma omp parallel num_threads(2)
        {
            #pragma omp single
            {
                printf("levels = %d \n", omp_get_level()); // сколько вложенных регионов
                
                printf("avtive levels = %d \n", omp_get_active_level()); // глубина активных вложенных регионов
                
                printf("id = %d \n", omp_get_ancestor_thread_num(2)); // номер потока с заданного уровня
                
                printf("size = %d \n", omp_get_team_size(2));
            }
        }
    }
    
    */
    
    return 0;
}
