#include <iostream>
#include <cmath>
#include "PauliX.hpp"

void PauliX::apply(std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int>& input) {

    auto& reg = std::get<0>(input);
    int index = std::get<1>(input);

    unsigned int z = 1 << index;

    for (unsigned int i = 0; i < reg->size(); i++) {
        if (!(i >> index & 1)) {
            unsigned int j = i ^ z;
            auto tmp = (*reg)[i];
            (*reg)[i] = (*reg)[j];
            (*reg)[j] = tmp;
        }
    }
}