#include <cstdio>

struct S
{
    char c{}; // 1 --> добавит ещё 7 нулевых байт
    double d{}; // 8
    int i{}; // 4 --> добавит ещё 4 нулевых байта
    // Размер кол-ва байт под поле стуркутры кратно размеру наибольшего поля
};

/* рекомендуется записывать поля по убыванию размера */

struct S1
{
    double d{}; // 8
    int i{}; // 4 
    char c{}; // 1 --> добавит ещё 3 нулевых байта
    // [8][4][4] --> кратно 8 
    // Адрес должен быть кратным наибольшему типу
};


// alignas (new_size_in_bytes) base_type object;
// alignas (double) int a;
// alignas (int) char;
// alignof (object/type) -- an alternative of sizeof()

int main()
{
    printf("Size of bad S = %ld\n", sizeof(S)); 
    printf("Size of good S = %ld\n", sizeof(S1)); 
    
    // Смотреть последнуюю цифру адреса
    int x{};
    printf("Addr  \'x\' = %p\n", &x); 
    
    alignas(16) int y{};
    printf("Addr  \'y\' = %p\n", &y); 
    
    
    //alignas (double) int a;
    //printf("%ld\n", alignof(a));    
    //printf("%ld\n", alignof(int)); 
    
    return 0;
}
