#include "Hadamard.hpp"
#include <cmath>
#include "omp.h"
#include <iostream>

Hadamard::Hadamard() {
    constant = 1./sqrt(2);
}

void Hadamard::apply(std::vector<double>& reg, int index) {

    int z = 1 << index;

    for (int i = 0; i < reg.size(); i++) {
        if (i >> index & 1) {
            int j = i ^ z;
            double tmp = reg[i];
            reg[i] = constant * (reg[j] - reg[i]);
            reg[j] = constant * (reg[j] + tmp);
        }
    }
}  
