#ifndef UNARY_GATE_HPP
#define UNARY_GATE_HPP

#include <complex>
#include <vector>
#include <utility>
#include <memory>

class UnaryGate {

public:
    virtual void apply(std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int>&) = 0;
}
;

#endif