#include <cstdio>
#include <omp.h> 

int main()
{
    int x{};
    #pragma omp parallel firstprivate(x) //иниц. x нулём в пар. рег
    {
        // сравнить 
        //#pragma omp single 
        #pragma omp single copyprivate(x) 
            x = 1;
        printf("(%d) x = %d\n", omp_get_thread_num(), x);
    }
    return 0;
}

