#include "QMem.hpp"
#include <cstdlib>
#include <iostream>

QMem::QMem(int _bits) : reg(pow(2,_bits)) {
    bits = _bits;
    reg[0] = 1;
}

int QMem::measure() {
    //measure all bits
    int randomVal = rand();
    double r = ((double) (randomVal % 100000)/ (100001));
    for (int i = 0; i < reg.size(); i++) {
        r -= reg[i] * reg[i];
        if (r < 0) {
            reg.clear();
            int reverse = 0;
            for (int j = 0; j < bits; j++) {
                if (i >> j & 1) {
                    reverse += 1 << (bits - j - 1);
                }
            }
            return reverse;
        }
    }
}

void QMem::apply(Gate& gate) {
    gate.apply(reg);
}

void QMem::apply(UnaryGate& gate, int idx) {
    gate.apply(reg, idx);
}

void QMem::apply(UnaryGate& gate, std::vector<int> idxs) {
    for (int i = 0; i < idxs.size(); i++) {
        gate.apply(reg, idxs[i]);
    }
}
