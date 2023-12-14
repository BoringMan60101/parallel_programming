#include <cstdio>

#include <omp.h>

int main()
{    
    int s{};
    
	#pragma omp parallel reduction(+:s)
    {
        for(int i = 0; i < 1000; i++)
            s += 1;
    }
    printf("s = %d\n", s);
	return 0;
}
