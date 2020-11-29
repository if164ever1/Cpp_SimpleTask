#include <iostream>
#include <initializer_list>
#include <stdarg.h>

template <typename T>
T minimun(T const a, T const b) {return a < b ? a : b;}

template <typename T1, typename... T>
T1 minimun(T1 a, T... args)
{
    return minimun(a, minimun(args...));
}



int main()
{
    std::cout << minimun(11,15,10,222,45);
    return 0;
}