#include <iostream>

using namespace std;

//compiling with g++ -Wall -O2 -fopt-info-vec prog_name.cpp 

int main()
{
    const int N{1024};
    int *a{new int [N]{}}, *b{new int [N]{}}, *c{new int [N]{}};
    
    for(int i = 0; i < N; i++)
        c[i] = a[i] + b[i];
    
    cout << c[0] << endl;
    
    return 0;
}
