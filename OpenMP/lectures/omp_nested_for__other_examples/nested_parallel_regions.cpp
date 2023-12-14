#include <cstdio>
#include <omp.h>

// Пример на функции для управления вложенным параллелизмом

int main()
{   
    
    printf("default nested parallel regions: %d\n", omp_get_nested());
    #pragma omp parallel num_threads(3)
    {

        // По умолчанию вложенные паралелльные регионы неактивны 
        #pragma omp parallel num_threads(2)
        {
            printf("Hello, World!\n");
        }
    }
    
    
    omp_set_nested(true);
    printf("\nafter omp_set_nested(1): %d\n", omp_get_nested());
    #pragma omp parallel num_threads(3)
    {
        // После применения omp_set_nested() вложенные пар. рег. становятся активными 
        #pragma omp parallel num_threads(2)
        {
            printf("Hello, World!\n");
        }
    }
    
    //Действие функций получения номера потока со вложенными регионами
    printf("\n\n");
    #pragma omp parallel num_threads(3)
    {
        // Вызовы omp_get_thread_num(), omp_get_thread_num()
        // Всегда привязываются к самому вложенному региону
        printf("_id=%d, threads:%d_\n", omp_get_thread_num(), omp_get_num_threads());
        
        #pragma omp parallel num_threads(2)
        {
            printf("id=%d, threads:%d\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }
    
    
    
    return 0;
}
