#include <chrono>
#include <iostream>

int main()
{
    //Ejemplo medición de tiempo
    auto begin = std::chrono::high_resolution_clock::now();
    // code to benchmark

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    return 0;
}
