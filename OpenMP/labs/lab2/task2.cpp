#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <omp.h>


//Умножение матрицы 'A' на вектор 'b' (в параллельном режиме)
int main()
{
    srand(time(nullptr));
    const int n{10}, m{9}; //n - кол-во строк, m - кол-во столбцов
    int A[n][m]{}, b[m]{};
    /*
    int A[n][m] = 
    {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
        
    };
    int b[m] = {1, 2, 3};
    */
    int c[n]{};
    
    
    //заполнение матрицы 'A' и вектора 'b'
    for(int j = 0; j < m; j++)
    {
        for(int i = 0; i < n; i++)
            A[i][j] = 1;//rand() % 6; // [1 - 5]
        b[j] = 1;
    }
    
    
    //вывод матрицы 'A'
    printf("\nMatrix A[%d][%d]\n", n, m);
    for(int i = 0; i < n; i++)
    {
        printf("|| ");
        for(int j = 0; j < m; j++)
            printf("%d ", A[i][j]);
        printf("||\n");
    }
    
    //вывод вектора 'b'
    printf("\nVector b[%d][1]\nb = { ", m);
    for(int j = 0; j < m; j++)
       printf("%d ", b[j]);
    printf("}\n");
    
    
    //умножение
    #pragma omp parallel for 
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            c[i] += A[i][j]*b[j];
    
    
    //вывод вектора 'c'
    printf("\nVector c[%d][1] = A[%d][%d]*b[%d][1]\nc = { ", n, n, m, m);
    for(int i = 0; i < n; i++)
       printf("%d ", c[i]);
    printf("}\n\n");
    
    return 0;
}
