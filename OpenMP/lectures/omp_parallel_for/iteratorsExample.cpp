#include <cstdio>
#include <omp.h>

#include <vector>

using namespace std;

int main()
{
    vector<int> A{1, 2, 3, 4, 5};
    
    //printf("%d\n", _OPENMP);
    #pragma omp parallel for
    for(auto it=A.begin(); it != A.end(); it++)
        *it += 10;
 
    for(int elem : A)
        printf("%d\n", elem);
    return 0;
}
