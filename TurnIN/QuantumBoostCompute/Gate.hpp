#ifndef QUANTUMGATE_HPP
#define QUANTUMGATE_HPP

#include <boost/compute/command_queue.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

class Gate
{
public:
    virtual void apply(compute::vector<float>&, compute::command_queue& queue) = 0;
    
};

#endif