#include <iostream>
#include "QMem.hpp"
#include <cstdlib>

namespace compute = boost::compute;

QMem::QMem(int _bits, compute::command_queue& _queue) 
    :bits(_bits), queue(_queue) , reg((int)pow(2,_bits) - 1,0., _queue)
    {
        reg.insert(reg.begin(), 1, queue);
    }

int QMem::measure() {
    //measure all bits

    std::vector<float> localReg(reg.size());

    compute::copy(
        reg.begin(), reg.end(),
                localReg.begin(),
        queue
    );

    

    int randomVal = rand();
    float r = ((float) (randomVal % 100000)/ (100001));
    for (int i = 0; i < localReg.size(); i++) {
        r -= localReg[i] * localReg[i];
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
    gate.apply(reg, queue);
}

void QMem::apply(UnaryGate& gate, int idx) {
    gate.apply(reg, idx, queue);
}

void QMem::apply(UnaryGate& gate, std::vector<int> idxs) {
    for (int i = 0; i < idxs.size(); i++) {
        gate.apply(reg, idxs[i], queue);
    }
}
