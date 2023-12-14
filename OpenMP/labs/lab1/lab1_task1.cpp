#include <cstdio>
#include <omp.h>

int main() {
    int s[4]{}; 
    
    #pragma omp parallel num_threads(9)
    {
        int id {omp_get_thread_num()};
        if(id % 2 == 0)
            printf("Even-numbered thread, id = %d\n", id);
        else
            printf("Odd-numbered thread, id = %d\n", id);
    }

    return 0;
}
