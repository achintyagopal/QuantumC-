#include "PauliZ.hpp"
#include <cmath>

void PauliZ::apply(std::vector<double>& reg, int index) {

    int z = 1 << index;

    for (int i = 0; i < reg.size(); i++) {
        if (i >> index & 1) {
            reg[i] *= -1;
        }
    }
}  