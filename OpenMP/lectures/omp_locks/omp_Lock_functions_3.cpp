#include <cstdio>
#include <omp.h>

/*
 Пример на множественное закрытие ключа (nested lock)
*/


int main()
{
    omp_nest_lock_t lock;
    omp_init_nest_lock(&lock);
    
    #pragma omp parallel 
    {
        
        #pragma omp single
        {
            printf("count = %d\n", omp_test_nest_lock(&lock));
            printf("count = %d\n", omp_test_nest_lock(&lock));
            
            omp_unset_nest_lock(&lock);
            omp_unset_nest_lock(&lock);
        }
    
    }
    
    omp_destroy_nest_lock(&lock);
    
    return 0;
}


