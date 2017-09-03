#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "Gate.hpp"
#include "UnaryGate.hpp"

class Control : public Gate
{
    UnaryGate& gate;
    std::vector<int> controlBits;
    std::vector<int> notControlBits;
    int index;
public:
    Control(UnaryGate& gate_, std::vector<int>& controlBits, std::vector<int>& notControlBits, int index);

    virtual void apply(std::vector<double>& reg);
};

#endif