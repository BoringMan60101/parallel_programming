#include <cstdio>
#include <omp.h>
#define THREADS_NUM 4

/*
Пример на средства синхронизации в OpenMP
Здесь имитируется работа директивы 'omp barrier'
*/

void myBadBarrier(const int id)
{
    static bool flags[THREADS_NUM]; // Изначально тут все false
    
    flags[id] = true;
    #pragma omp flush
    
    int sum = 0;
    do
    {
        sum = 0;
        for(int i = 0; i < THREADS_NUM; i++)
            sum += flags[i] ? 1 : 0;
    } while(sum < THREADS_NUM);
}

int main()
{
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

        // Все потоки кроме 'id=0' простаивают, пока число 'x' не введено
        //#pragma omp barrier
        myBadBarrier(omp_get_thread_num());

        printf("output (id=%d)\n", omp_get_thread_num());
    }

    return 0;
}
