#include <iostream>
#include <immintrin.h> // vector operations

using namespace std;

int main()
{
    // epi = extented packed integers
    // setr = set reverse: [11, 22, 33, 44] 
    // there is _mm_set_epi32 
    // big/little endian
    // _mm_set_epi32(1, 2, 3, 4) --> [4, 3, 2, 1];
    
    /*
    __m128i va, vb, vc; // va = 4 numbers of 32 bits
    va = _mm_setr_epi32(11, 22, 33, 44);
    vb = _mm_setr_epi32(1, 2, 3, 4);
    vc = _mm_add_epi32(va, vb);
    
     using 'for' is prohibited
    // _mm_extract_epi32(__m128i, const unsigned);
    cout << _mm_extract_epi32(vc, 0) << endl;
    cout << _mm_extract_epi32(vc, 1) << endl;
    cout << _mm_extract_epi32(vc, 2) << endl;
    cout << _mm_extract_epi32(vc, 3) << endl;
    */
    
    __m128i va, vb, vc; 
    int a[4]{11, 22, 33, 44}, b[4]{1, 2, 3, 4}, c[4]{};
    va = _mm_loadu_si128((__m128i *) a); // 'u' - unaligned 
    vb = _mm_loadu_si128((__m128i *) b);
    vc = _mm_add_epi32(va, vb);
    _mm_storeu_si128((__m128i *) c, vc);
    for(int i = 0; i < 4; i++)
        cout << c[i] << " ";
    cout << endl;
    
    // Faster variant
    alignas(16) int A[4]{11, 22, 33, 44};
    alignas(16) int B[4]{1, 2, 3, 4};
    alignas(16) int C[4]{};
    va = _mm_load_si128((__m128i *) A);
    vb = _mm_load_si128((__m128i *) B);
    vc = _mm_add_epi32(va, vb);
    _mm_store_si128((__m128i *) C, vc);
    for(int i = 0; i < 4; i++)
        cout << C[i] << " ";
    cout << endl;
    
    return 0;
}
