#include "PauliX.hpp"
#include <cmath>
#include "omp.h"

void PauliX::apply(std::vector<double>& reg, int index) {

    int z = 1 << index;

    if (index == 0) {
        #pragma omp parallel for
        for (int i = 0; i < reg.size(); i+=2) {
            int j = i ^ z;
            double tmp = reg[i];
            reg[i] = reg[j];
            reg[j] = tmp;
        }
    } else if(reg.size() >> index & 1) {
        #pragma omp parallel for
        for (int i = 0; i < reg.size() / 2; i++) {
            int j = i ^ z;
            double tmp = reg[i];
            reg[i] = reg[j];
            reg[j] = tmp;
        }
    } else if (index == 1) {
        #pragma omp parallel for
        for (int i = 0; i < reg.size(); i+=4) {
            int j = i ^ z;
            double tmp = reg[i];
            reg[i] = reg[j];
            reg[j] = tmp;

            j = (i+1) ^ z;
            tmp = reg[i+1];
            reg[i+1] = reg[j];
            reg[j] = tmp;
        }
    } else if (index == 2) {
        #pragma omp parallel for
        for (int i = 0; i < reg.size(); i+=8) {
            int j = i ^ z;
            double tmp = reg[i];
            reg[i] = reg[j];
            reg[j] = tmp;

            j = (i+1) ^ z;
            tmp = reg[i+1];
            reg[i+1] = reg[j];
            reg[j] = tmp;

            j = (i+2) ^ z;
            tmp = reg[i+2];
            reg[i+2] = reg[j];
            reg[j] = tmp;

            j = (i+3) ^ z;
            tmp = reg[i+3];
            reg[i+3] = reg[j];
            reg[j] = tmp;
        }
    } else {
        #pragma omp parallel for
        for (int i = 0; i < reg.size(); i+=8) {
            if (!(i >> index & 1)) {
                int j = i ^ z;
                double tmp = reg[i];
                reg[i] = reg[j];
                reg[j] = tmp;

                j = (i+1) ^ z;
                tmp = reg[i+1];
                reg[i+1] = reg[j];
                reg[j] = tmp;

                j = (i+2) ^ z;
                tmp = reg[i+2];
                reg[i+2] = reg[j];
                reg[j] = tmp;

                j = (i+3) ^ z;
                tmp = reg[i+3];
                reg[i+3] = reg[j];
                reg[j] = tmp;
                
                j = (i+4) ^ z;
                tmp = reg[i+4];
                reg[i+4] = reg[j];
                reg[j] = tmp;

                j = (i+5) ^ z;
                tmp = reg[i+5];
                reg[i+5] = reg[j];
                reg[j] = tmp;

                j = (i+6) ^ z;
                tmp = reg[i+6];
                reg[i+6] = reg[j];
                reg[j] = tmp;

                j = (i+7) ^ z;
                tmp = reg[i+7];
                reg[i+7] = reg[j];
                reg[j] = tmp;
            }
        }
    }

    // for (int i = 0; i < reg.size(); i++) {
    //     if (i >> index & 1) {
    //         int j = i ^ z;
    //         double tmp = reg[i];
    //         reg[i] = reg[j];
    //         reg[j] = tmp;
    //     }
    // }
}  