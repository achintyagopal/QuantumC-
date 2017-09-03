#ifndef QMEM_HPP
#define QMEM_HPP

#include "Gate.hpp"
#include "UnaryGate.hpp"
#include <vector>
#include <cmath>

class QMem
{
    int bits;
    std::vector<double> reg;
public:
    QMem(int _bits);

    int measure();
    void apply(Gate& gate);
    void apply(UnaryGate& gate, int idx);
    void apply(UnaryGate& gate, std::vector<int> idxs);
};

#endif