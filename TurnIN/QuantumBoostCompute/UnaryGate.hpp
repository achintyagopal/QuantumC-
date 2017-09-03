#ifndef UNARYGATE_HPP
#define UNARYGATE_HPP

#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

class UnaryGate
{
public:
    virtual void apply(compute::vector<float>&, int idx, compute::command_queue& queue) = 0;    
};

#endif