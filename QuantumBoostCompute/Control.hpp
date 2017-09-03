#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "Gate.hpp"
#include "UnaryGate.hpp"
#include <boost/compute/command_queue.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

class Control : public Gate
{
    UnaryGate& gate;
    std::vector<int> controlBits;
    std::vector<int> notControlBits;
    int index;
    compute::kernel kernel;
    compute::kernel kernel2;
public:
    Control(UnaryGate& gate_, std::vector<int>& controlBits, std::vector<int>& notControlBits, int index, compute::context& context);

    virtual void apply(compute::vector<float>& reg, compute::command_queue& queue);
};

#endif