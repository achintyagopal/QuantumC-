#ifndef HADAMARD_HPP
#define HADAMARD_HPP

#include "UnaryGate.hpp"

class Hadamard : public UnaryGate
{
    double constant;
public:
    Hadamard();

    virtual void apply(std::vector<double>& reg, int idx);
};

#endif