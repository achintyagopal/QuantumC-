#include "omp.h"
#include <iostream>
#include <cmath>
#include "Hadamard.hpp"

void Hadamard::apply(std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int>& input) {

    auto& reg = std::get<0>(input);
    int index = std::get<1>(input);

    unsigned int z = 1 << index;
    double c = 1.0 / sqrt(2);

    #pragma omp parallel for
    for (unsigned int i = 0; i < reg->size(); i++) {
        if (!(i >> index & 1)) {
            unsigned int j = i ^ z;
            auto tmp = (*reg)[i];
            if (j > reg->size()) {
                std::cout << i << " " << j << " " << reg->size() << "\n";
            }
            (*reg)[i] = c * ((*reg)[j] + (*reg)[i]);
            (*reg)[j] = c * (tmp - (*reg)[j]);
        }
    }
}
