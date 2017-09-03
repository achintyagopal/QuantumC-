#ifndef PAULIZ_HPP
#define PAULIZ_HPP

#include "UnaryGate.hpp"

class PauliZ : public UnaryGate
{
public:
    virtual void apply(std::vector<double>& reg, int idx);
};

#endif