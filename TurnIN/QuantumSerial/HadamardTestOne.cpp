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
    qmem.apply(hadamard, 0);
    return 0;
}