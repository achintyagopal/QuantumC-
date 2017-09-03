#ifndef PAULIX_HPP
#define PAULIX_HPP

#include <complex>
#include <vector>
#include <utility>
#include <memory>

#include "UnaryGate.hpp"

class PauliX : public UnaryGate {

public:
    virtual void apply(std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int>&);
};

#endif