#ifndef PAULIX_HPP
#define PAULIX_HPP

#include "UnaryGate.hpp"

#include <boost/compute/command_queue.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

class PauliX : public UnaryGate
{
    compute::kernel kernel;
public:
    PauliX(compute::context& context);
    virtual void apply(compute::vector<float>& reg, int idx, compute::command_queue& queue);
};

#endif