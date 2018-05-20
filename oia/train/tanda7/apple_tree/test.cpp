// #include <stdio>
#include <fstream>
#include <random>
#include <time.h>

int main() {
    srand(time(NULL));
    std::ofstream test("5.in");
    int n = rand() % 100000;

    test << n << std::endl;
    for(int i = 1; i < n; ++i) {
        // test << rand() % i << " ";
        test << i - 1 << " ";
    }
    test << std::endl;

    for(int i = 0; i < n; ++i) {
        test << rand() % 2 << " ";
    }
    test << std::endl;
}
