#include <cstdio>
#include <omp.h> 

int main()
{
    int x{};
    #pragma omp parallel sections lastprivate(x)
    {
        #pragma omp section
            x = 1;

        #pragma omp section
            x = 2;
    }
                     
    printf("x = %d\n", x);
    return 0;
}

/*
     #pragma omp parallel 
    {
        #pragma omp sections
        {
            #pragma omp section
                { code }
            
            #pragma omp section
                { code }
            
            #pragma omp section
                { code }
            
        }
    }
     */
