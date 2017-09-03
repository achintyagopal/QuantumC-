#include <cstdlib>
#include <iostream>
#include "Hadamard.hpp"
#include "QMem.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cout << "Not enough cmd line args\n";
        return -1;
    }
    srand(time(NULL));
    
    int bits = std::stoi(argv[1]);
    Hadamard hadamard;
    QMem qmem(bits);
    for (int i = 0; i < bits; i++) {
        qmem.apply(hadamard, i);
    }
    return 0;
}