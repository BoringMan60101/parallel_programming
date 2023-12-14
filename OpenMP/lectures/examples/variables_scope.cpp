#include <cstdio>
//#include <omp.h>

// Пример на то, как в OpenMP определяются частные и общие перменные

int foo() 
{
    static int x{}; // по умолчанию общие 
    x++;
    return x;
}


// Здесь a, b, x по умолчанию частные
int func(int a, int b) 
{
    int x{};  
    x++;
    return x;
}


int main() 
{
    #pragma omp parallel // вывод x=1, x=2 всегда
    {
        #pragma omp single
            printf("x = %d\n", foo());
        #pragma omp single
            printf("x = %d\n", foo());
    }
    
    
    
    // Как НЕЛЬЗЯ делать
    #pragma omp parallel num_threads(8)
    {
        foo();
    }
    printf("wonrg x = %d (run many times)\n", foo() - 1);
    
    return 0;
}
