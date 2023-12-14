#include <cstdio>
#include <cstdlib>
#include <ctime>

/*
 Пример параллелизма в виде "конвейера"
 Есть набор однотипных задач, состоящих из нескольких этапов.
 Потоки последовательно начинают выполнять задачи.

 (Показаны "временные промежутки" З - Задача, Э - Этап)
 1: поток выполняет З1.Э1 (2, 3, 4: простаивают)

 1: 32.Э1, 2: 31.Э2 (3, 4: простаивают)

 1: З3.Э1, 2: 32.Э2, 3: 31.Э3 (4: простаивает)

 и так далее ...

 ==============================================================================
 В данном случае задачи это: обработка матриц.
 поток "1" --- создаёт матрицу
 поток "2" --- находит минимум
 поток "3" --- находит максимум
 поток "4" --- выводит матрицу, минимум, максимум
 Конвейер реализован с помощью 4-х общих массивов с флагами.
 Каждый поток может изменять флаги только в соот-щем ему массиве,
 но в процессе работы он читает флаги из других массивов.
*/

const int M = 5; // Кол-во матриц для обработки
const int n = 3, m = 3; // Размерность матриц

void initMatrix(int mat_idx, int M[][n][m]);

int findMin(int mat_idx, const int M[][n][m]);

int findMax(int mat_idx, const int M[][n][m]);

void printMatrix(int mat_idx, const int M[][n][m]);


int main()
{
    srand(time(nullptr));
    int matrices[M][n][m];

    // Массивы с флагами для управления между секциями
    bool created[M];
    bool foundMin[M];
    bool foundMax[M];
    for(int i = 0; i < M; i++)
        created[i] = foundMin[i] = foundMax[i] = false;

    int minValues[M], maxValues[M];

    
    #pragma omp parallel sections \
    num_threads(4) \
    shared(created, foundMin, foundMax, minValues, maxValues)
    {
        // Поток, инициализирующий матрицы
        #pragma omp section 
        {
            for(int mat = 0; mat < M; mat++)
            {
                initMatrix(mat, matrices);
                created[mat] = true;
                #pragma omp flush 
            }
        }
        
        // Поток, находящий минимум в матрице
        #pragma omp section
        {
            for(int mat = 0; mat < M; mat++)
            {
                while(created[mat] == false)
                {
                    #pragma omp flush 
                }

                minValues[mat] = findMin(mat, matrices);
                foundMin[mat] = true;
                #pragma omp flush 
            }
        }

        // Поток, находящий максимум в матрице
        #pragma omp section
        {
            for(int mat = 0; mat < M; mat++)
            {
                while(created[mat] == false)
                {
                    #pragma omp flush 
                }

                maxValues[mat] = findMax(mat, matrices);
                foundMax[mat] = true;
                #pragma omp flush 
            }
        }

        // Поток, выводящий матрицы
        #pragma omp section 
        {
            for(int mat = 0; mat < M; mat++)
            {
                while((foundMin[mat] && foundMax[mat]) == false)
                {
                    #pragma omp flush 
                }

                printf("matrix %d: min=%d, max=%d\n", mat+1, minValues[mat], maxValues[mat]);
                printMatrix(mat, matrices);
                printf("\n");
                #pragma omp flush 
            }
        }
    }
    
    return 0;
}


void initMatrix(int mat_idx, int M[][n][m])
{
    for(int row = 0; row < n; row++)
        for(int col = 0; col < m; col++)
            M[mat_idx][row][col] = rand() % 11;
}


int findMin(int mat_idx, const int M[][n][m])
{
    int min = M[mat_idx][0][0];
    for(int row = 0; row < n; row++)
        for(int col = 0; col < m; col++)
            if(M[mat_idx][row][col] < min)
                min = M[mat_idx][row][col];
    return min;
}


int findMax(int mat_idx, const int M[][n][m])
{
    int max = M[mat_idx][0][0];
    for(int row = 0; row < n; row++)
        for(int col = 0; col < m; col++)
            if(M[mat_idx][row][col] > max)
                max = M[mat_idx][row][col];
    return max;
}


void printMatrix(int mat_idx, const int M[][n][m])
{
    for(int row = 0; row < n; row++)
    {
        for(int col = 0; col < m; col++)
            printf("%d  ", M[mat_idx][row][col]);
        printf("\n");
    }
}
