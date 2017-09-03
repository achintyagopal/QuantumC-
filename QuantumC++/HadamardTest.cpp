#include "src/QMem.hpp"
#include "src/unarygates/Hadamard.hpp"
// #include "src/gates/Hadamard.cpp"
#include <vector>
#include <complex>
#include <iostream>
#include <cmath>

int main(int argc, char const *argv[])
{   
    int bits = 22;
    Hadamard h;

    QMem qMem(bits);
    
    int idx = qMem.alloc(bits);
    std::vector<int> idxs(bits);
    for (int i = 0; i< bits; i++) {
        idxs[i] = idx + i;
    }

    qMem.apply(h, idxs);
    return 0;
}