#include <cstdio>
#include <omp.h>
#define THREADS_NUM 4

/*
Пример на средства синхронизации в OpenMP
Здесь имитируется работа директивы 'omp barrier'
С помощью механизма 'замков' стандарта OpenMP
*/

int main()
{
    omp_lock_t lock;
    omp_init_lock(&lock);

    int reachedThreadsSum = 0;

    #pragma omp parallel num_threads(THREADS_NUM) shared(reachedThreadsSum)
    {
        // Чтобы все ждали, пока будет введён 'x' в потоке с индексом '0'
        if(omp_get_thread_num() == 0)
        {
            int x;
            printf("Enter x\n");
            scanf("%d", &x);
        }

        //#pragma omp barrier

        // ########## Код для имитации директивы omp barrier
        // Все потоки, кроме одного (id = 0) будут простаивать
        omp_set_lock(&lock);
        reachedThreadsSum += 1;
        #pragma omp flush
        omp_unset_lock(&lock);

        while(reachedThreadsSum != THREADS_NUM)
        {
            #pragma omp flush
        }

        printf("output (id=%d)\n", omp_get_thread_num());
    }

    omp_destroy_lock(&lock);
    return 0;
}
