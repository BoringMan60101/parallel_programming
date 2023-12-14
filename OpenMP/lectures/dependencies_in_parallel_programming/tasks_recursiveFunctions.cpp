#include <cstdio>
#include <unistd.h>
#include <omp.h>

// Пример рекурсивного выполнения задач (omp tasks)
// Правило переменных по умолчанию для задач

int worngFib(int n)
{
    int a, b; 
    if(n < 2)
        return n;
    
    #pragma omp task
        a = worngFib(n-1);
    // Переменные 'a' в функции (сначала) и 'a' в задачах 
    // Это разные переменные! 
    // По умолчанию в каждой задаче переменные не являющиеся общими
    // В котексте потока, создающего задачу 
    // Эти переменные становятся firstprivate
        
    #pragma omp task
        b = worngFib(n-2);
        
    #pragma omp taskwait
        return a + b;
        
    // Переменные 'n' в аргументе функции, и при двух вызовах это
    // 3 разных веременных. В данном случае 'n' копируется 
}


int Fib(int n)
{
    int a, b; 
    if(n < 2)
        return n;
    
    #pragma omp task shared(a)
        a = Fib(n-1); // 'n' - это firstprivate
    
        
    #pragma omp task shared(b)
        b = Fib(n-2); // 'n' - это firstprivate
        
    #pragma omp taskwait
        return a + b;
}


int main()
{
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("F_%d = %d\n", 6, Fib(6));
        }
    }
    
    return 0;
}
