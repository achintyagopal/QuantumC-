#ifndef UNARYGATE_HPP
#define UNARYGATE_HPP

#include <vector>

class UnaryGate
{
public:
    virtual void apply(std::vector<double>&, int idx) = 0;    
};

#endif