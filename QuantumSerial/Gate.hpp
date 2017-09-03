#ifndef GATE_HPP
#define GATE_HPP

#include <vector>

class Gate
{
public:
    virtual void apply(std::vector<double>& ) = 0;
    
};

#endif