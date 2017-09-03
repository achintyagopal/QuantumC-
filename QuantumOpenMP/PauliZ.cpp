#include "omp.h"
#include "PauliZ.hpp"
#include <cmath>

void PauliZ::apply(std::vector<double>& reg, int index) {

    if (index == 0) {
        #pragma omp parallel for
        for (int i = 1; i < reg.size(); i+=2) {
            // int j = i ^ z;
            reg[i] *= -1;
        }
    } else if(reg.size() >> index & 1) {
        #pragma omp parallel for
        for (int i = reg.size() / 2; i < reg.size(); i++) {
            reg[i] *= -1;
        }
    } else if (index == 1) {
        #pragma omp parallel for
        for (int i = 2; i < reg.size(); i+=4) {
            reg[i] *= -1;
            reg[i+1] *= -1;

        }
    } else if (index == 2) {
        #pragma omp parallel for
        for (int i = 4; i < reg.size(); i+=8) {
            reg[i] *= -1;
            reg[i+1] *= -1;
            reg[i+2] *= -1;
            reg[i+3] *= -1;
        }
    } else {
        #pragma omp parallel for
        for (int i = 0; i < reg.size(); i+=8) {
            if ((i >> index & 1)) {
                reg[i] *= -1;
                reg[i+1] *= -1;
                reg[i+2] *= -1;
                reg[i+3] *= -1;
                reg[i+4] *= -1;
                reg[i+5] *= -1;
                reg[i+6] *= -1;
                reg[i+7] *= -1;
            }
        }
    }

    // for (int i = 0; i < reg.size(); i++) {
    //     if (i >> index & 1) {
    //         reg[i] *= -1;
    //     }
    // }
}  