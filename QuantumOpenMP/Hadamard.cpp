#include "Hadamard.hpp"
#include <cmath>
#include "omp.h"

Hadamard::Hadamard() {
    constant = 1./sqrt(2);
}

void Hadamard::apply(std::vector<double>& reg, int index) {

    int z = 1 << index;

    // if (index == 0) {
    //     #pragma omp parallel for
    //     for (int i = 0; i < reg.size(); i+=2) {
    //         int j = i ^ z;
    //         double tmp = reg[i];
    //         reg[i] = constant * (reg[j] + reg[i]);
    //         reg[j] = constant * (tmp - reg[j]);
    //     }
    // } else if(reg.size() >> index & 1) {
    //     #pragma omp parallel for
    //     for (int i = 0; i < reg.size() / 2; i++) {
    //         int j = i ^ z;
    //         double tmp = reg[i];
    //         reg[i] = constant * (reg[j] + reg[i]);
    //         reg[j] = constant * (tmp - reg[j]);
    //     }
    // } else if (index == 1) {
    //     #pragma omp parallel for
    //     for (int i = 0; i < reg.size(); i+=4) {
    //         int j = i ^ z;
    //         double tmp = reg[i];
    //         reg[i] = constant * (reg[j] + reg[i]);
    //         reg[j] = constant * (tmp - reg[j]);

    //         j = (i+1) ^ z;
    //         tmp = reg[i+1];
    //         reg[i+1] = constant * (reg[j] + reg[i+1]);
    //         reg[j] = constant * (tmp - reg[j]);
    //     }
    // } else if (index == 2) {
    //     #pragma omp parallel for
    //     for (int i = 0; i < reg.size(); i+=8) {
    //         int j = i ^ z;
    //         double tmp = reg[i];
    //         reg[i] = constant * (reg[j] + reg[i]);
    //         reg[j] = constant * (tmp - reg[j]);

    //         j = (i+1) ^ z;
    //         tmp = reg[i+1];
    //         reg[i+1] = constant * (reg[j] + reg[i+1]);
    //         reg[j] = constant * (tmp - reg[j]);

    //         j = (i+2) ^ z;
    //         tmp = reg[i+2];
    //         reg[i+2] = constant * (reg[j] + reg[i+2]);
    //         reg[j] = constant * (tmp - reg[j]);

    //         j = (i+3) ^ z;
    //         tmp = reg[i+3];
    //         reg[i+3] = constant * (reg[j] + reg[i+3]);
    //         reg[j] = constant * (tmp - reg[j]);
    //     }
    // } else {
    //     #pragma omp parallel for
    //     for (int i = 0; i < reg.size(); i+=8) {
    //         if (!(i >> index & 1)) {
    //             int j = i ^ z;
    //             double tmp = reg[i];
    //             reg[i] = constant * (reg[j] + reg[i]);
    //             reg[j] = constant * (tmp - reg[j]);

    //             j = (i+1) ^ z;
    //             tmp = reg[i+1];
    //             reg[i+1] = constant * (reg[j] + reg[i+1]);
    //             reg[j] = constant * (tmp - reg[j]);

    //             j = (i+2) ^ z;
    //             tmp = reg[i+2];
    //             reg[i+2] = constant * (reg[j] + reg[i+2]);
    //             reg[j] = constant * (tmp - reg[j]);

    //             j = (i+3) ^ z;
    //             tmp = reg[i+3];
    //             reg[i+3] = constant * (reg[j] + reg[i+3]);
    //             reg[j] = constant * (tmp - reg[j]);

    //             j = (i+4) ^ z;
    //             tmp = reg[i+4];
    //             reg[i+4] = constant * (reg[j] + reg[i+4]);
    //             reg[j] = constant * (tmp - reg[j]);

    //             j = (i+5) ^ z;
    //             tmp = reg[i+5];
    //             reg[i+5] = constant * (reg[j] + reg[i+5]);
    //             reg[j] = constant * (tmp - reg[j]);

    //             j = (i+6) ^ z;
    //             tmp = reg[i+6];
    //             reg[i+6] = constant * (reg[j] + reg[i+6]);
    //             reg[j] = constant * (tmp - reg[j]);

    //             j = (i+7) ^ z;
    //             tmp = reg[i+7];
    //             reg[i+7] = constant * (reg[j] + reg[i+7]);
    //             reg[j] = constant * (tmp - reg[j]);
    //         }
    //     }
    // }

    #pragma omp parallel for //schedule(guided)
    for (int i = 0; i < reg.size(); i++) {
        if (i >> index & 1) {
            int j = i ^ z;
            double tmp = reg[i];
            reg[i] = constant * (reg[j] - reg[i]);
            reg[j] = constant * (reg[j] + tmp);
        }
    }

    // int c = pow(2, index + 1);

    // #pragma omp parallel for schedule(guided)
    // for (int k = 0; k < reg.size(); k+=c) {
    //     int d = k + pow(2,index);
    //     for(int i = k; i < d; i++) {
    //         int j = i ^ z;
    //         double tmp = reg[i];
    //         reg[i] = constant * (reg[j] - reg[i]);
    //         reg[j] = constant * (reg[j] + tmp);
    //     }
    // }
}  
