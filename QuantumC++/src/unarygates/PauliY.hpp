#ifndef PAULIY_HPP
#define PAULIY_HPP

#include <complex>
#include <vector>
#include <utility>
#include <memory>
#include "UnaryGate.hpp"

class PauliY : public UnaryGate {

public:
    virtual void apply(std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int>&);
};

#endif