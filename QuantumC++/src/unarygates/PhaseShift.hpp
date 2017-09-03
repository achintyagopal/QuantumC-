#ifndef PHASE_SHIFT_HPP
#define PHASE_SHIFT_HPP

#include <complex>
#include <vector>
#include <utility>
#include <memory>
#include "UnaryGate.hpp"

class PhaseShift : public UnaryGate {
    std::complex<double> constant;
public:
    PhaseShift(double angle);
    virtual void apply(std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int>&);
};

#endif