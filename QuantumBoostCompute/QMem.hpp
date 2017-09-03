#ifndef QMEM_HPP
#define QMEM_HPP

#include "Gate.hpp"
#include "UnaryGate.hpp"
#include <vector>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

class QMem
{
    int bits;
    compute::vector<float> reg;
    compute::command_queue queue;

public:
    QMem(int _bits, compute::command_queue& queue);

    int measure();
    void apply(Gate& gate);
    void apply(UnaryGate& gate, int idx);
    void apply(UnaryGate& gate, std::vector<int> idxs);
};

#endif