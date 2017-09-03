#include "PauliX.hpp"
#include <cmath>

void PauliX::apply(std::vector<double>& reg, int index) {

    int z = 1 << index;

    for (int i = 0; i < reg.size(); i++) {
        if (i >> index & 1) {
            int j = i ^ z;
            double tmp = reg[i];
            reg[i] = reg[j];
            reg[j] = tmp;
        }
    }
}  