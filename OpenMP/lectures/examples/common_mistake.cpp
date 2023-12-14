//Пример ошибки при использовании общей переменной
//g++ -fopenmp ex_0.cpp
#include <cstdio>
#include <omp.h>

int main() {
    int s{}; //общая
    
    #pragma omp parallel
    {
        int id {omp_get_thread_num()};
        for(int i = 0; i < 1000; i++)
            s++;
    }
    
    printf("s = %d\n", s);
    return 0;
}
