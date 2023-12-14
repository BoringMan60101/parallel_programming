#include <cstdio>
#include <omp.h>


/*
 Пример на использование ключей (locks) в OpenMP
*/

int main()
{
    omp_lock_t lock;
    omp_init_lock(&lock);
    int x{};
    
    #pragma omp parallel num_threads(3) shared(x, lock)
    {
        omp_set_lock(&lock);
        x += 1;
        omp_unset_lock(&lock);
    }
    
    omp_destroy_lock(&lock);
    printf("x = %d\n", x);
    return 0;
}


