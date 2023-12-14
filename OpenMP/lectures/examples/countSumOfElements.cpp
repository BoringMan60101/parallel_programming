#include <cstdio>
#include <omp.h>
#include <numeric>
#include <iterator>

//Вычисление суммы элементов средствами openMP 

int main()
{
    const int N{100};
    int a[N]{}, s{};
    
    std::iota(std::begin(a), std::end(a), 0); //Заполнение массива [0; 99]
    
    #pragma omp parallel shared(a, s)
    {
        #pragma omp for reduction(+ : s)
        for(int i = 0; i < N; i++)
            s += a[i]; //для каждого потока в
                       //параллельном регионе 
                       //свой экземпляр переменной 's'
    }
    printf("s = %d\n", s);
    return 0;
}
