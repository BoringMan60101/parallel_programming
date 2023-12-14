#include <cstdio>
#include <omp.h>


/*
 Пример на функцию закрытие ключа без блокирования (omp_test_lock()) 
*/

int main()
{
    omp_lock_t lock;
    omp_init_lock(&lock);
    #pragma omp parallel num_threads(3) shared(lock)
    {
        while(!omp_test_lock(&lock)) //тут можно одни действия
            printf("Thread %d is waiting\n", omp_get_thread_num());
        
        printf("Thread %d is working\n", omp_get_thread_num()); //тут другие действия
        omp_unset_lock(&lock);
    }
    
    omp_destroy_lock(&lock);
    
    return 0;
}


