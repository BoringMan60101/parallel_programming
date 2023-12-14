/*
В этой задаче нужно найти максимум по массиву
С помощью метода деления на половины

Обработка массивы выполняется рекурсивно, вызовы параллельные (omp task)
*/

#include <cstdio>
#include <cstdlib>
#include <ctime>

int findMaxInArray(int const n, int const * arr)
{
    if(n <= 1)
        return arr[0];
    
    int max1, max2; // (#)
    
    #pragma omp task shared(max1)
        max1 = findMaxInArray(n/2, arr + 0); // (##)
    
    #pragma omp task shared(max2)
        max2 = findMaxInArray(n/2 + (n % 2), arr + n/2);
    
    #pragma omp taskwait
    
    return (max1 < max2) ? max2 : max1;
    /*
    Переменные max1 в (#) и (##) 'разные'
    В (#) max1 не проинициализорована (произвольное значение у неё)
    В (##) max1 будет найдена
    Но после этого, если не указать явно, что max1 ОБЩАЯ (shared)
    То это найденное значение забудется
    
    В итоге, если не указывать явно то, что max1, max2 общие
    Их значения остаются произвольными
    
    
    Про необходимость ожидания завершения задач (taskwait):
    Если этого не сделать, то 
    */
}

int main()
{
    //int const n = 6;
    //int arr[n] = {1, 3, 50, 2, 4, 8};
    int const n = 7;
    int arr[n];
    
    srand(time(nullptr));
    printf("Array witn %d integer elements:\n", n);
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i] = rand() % (n+1) );
    printf("\n");
    
    int max {-RAND_MAX};
    
    #pragma omp parallel
        #pragma omp single
            max = findMaxInArray(n, arr); // Внутри функции порождаются задачи
            // Эти задачи выполняются разными потоками (параллельно получается)
    
    printf("Max = %d \n", max);
    
    return 0;
}
