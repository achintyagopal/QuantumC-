#include "Hadamard.hpp"
#include "QMem.hpp"

int main(int argc, char const *argv[])
{
    int bits = 4;
    Hadamard hadamard;
    QMem qmem(bits);
    for (int i = 0; i < bits; i++) {
        qmem.apply(hadamard, i);
    }
    return 0;
}