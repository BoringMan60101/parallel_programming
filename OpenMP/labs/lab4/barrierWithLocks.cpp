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
        while(omp_test_lock(&lock) == 0)
        {
            #pragma omp flush
        }

            //if(reachedThreadsSum == THREADS_NUM)
                //break;

        //Этот инкремент будет выполняться в каждый момент времени ТОЛЬКО ОДНИМ потоком (1)
        //Причем он должен каждый раз выполняться НОВЫМ потоком (2)
        //Программа выполняется "сверху-вниз", критерий (2) выполняется автоматически
        #pragma omp flush
            reachedThreadsSum += 1;
        omp_unset_lock(&lock);

        while(reachedThreadsSum != THREADS_NUM)
        {
            #pragma omp flush
        }
        // ########## Код для имитации директивы omp barrier


        printf("output (id=%d)\n", omp_get_thread_num());
    }

    omp_destroy_lock(&lock);
    return 0;
}
