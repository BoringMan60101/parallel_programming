#include <cstdio>
#include <unistd.h>

int main()
{
    int x{}, y{};
    #pragma omp parallel
        #pragma omp single
        {
            #pragma omp taskgroup // comment it and compare output
                #pragma omp task
                {
                    x = 111;
                    #pragma omp task
                    {
                        sleep(1);
                        y = 222;
                    }
                }
            printf("x = %d, y = %d\n", x, y);
        }    
    return 0;
}
