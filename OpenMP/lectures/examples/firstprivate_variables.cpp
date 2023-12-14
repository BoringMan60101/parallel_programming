#include <cstdio>

#include <omp.h>

int main()
{    
    int x{111};
    
	#pragma omp parallel firstprivate(x)
    {
        x = 100;
        printf("x = %d\n", x);
    }
    printf("x = %d\n", x);
	return 0;
}
