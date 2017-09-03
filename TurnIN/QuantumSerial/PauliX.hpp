#ifndef PAULIX_HPP
#define PAULIX_HPP

#include "UnaryGate.hpp"

class PauliX : public UnaryGate
{
public:

    virtual void apply(std::vector<double>& reg, int idx);
};

#endif